/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details:
 *
 * Author: Petr Krasnoshchekov <petr.krasnoshchekov@wirenboard.com>
 *
 * Copyright (C) 2025 Wiren Board
 */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <gpiod.h>

#include "gpio-helper.h"

static int
chip_dir_filter (const struct dirent *entry)
{
    struct stat sb;
    int ret = 0;
    char *path;

    if (asprintf(&path, "/dev/%s", entry->d_name) < 0) {
        return 0;
    }

    if ((lstat(path, &sb) == 0) && (!S_ISLNK(sb.st_mode)) &&
        gpiod_is_gpiochip_device(path)) {
        ret = 1;
    }

    free(path);

    return ret;
}

static int
all_chip_paths (char ***paths_ptr)
{
    int i, j, num_chips, ret = 0;
    struct dirent **entries;
    char **paths;

    num_chips = scandir("/dev/", &entries, chip_dir_filter, versionsort);
    if (num_chips < 0) {
        // Unable to scan /dev
        return 0;
    }

    paths = calloc(num_chips, sizeof(*paths));
    if (paths == NULL) {
        // Out of memory
        return 0;
    }

    for (i = 0; i < num_chips; i++) {
        if (asprintf(&paths[i], "/dev/%s", entries[i]->d_name) < 0) {
            for (j = 0; j < i; j++)
                free(paths[j]);

            free(paths);
            return 0;
        }
    }

    *paths_ptr = paths;
    ret = num_chips;

    for (i = 0; i < num_chips; i++) {
        free(entries[i]);
    }

    free(entries);
    return ret;
}

void
gpio_line_find(const char *label, struct gpiod_chip **chip, unsigned int *offset)
{
    char **paths;
    int i;
    int num_chips;
    *chip = NULL;
    *offset = 0;

    num_chips = all_chip_paths(&paths);
    for (i = 0; i < num_chips; i++) {
        if (!*chip) {
            *chip = gpiod_chip_open(paths[i]);
            if (*chip) {
                *offset = gpiod_chip_get_line_offset_from_name(*chip, label);
            }
        }
        free(paths[i]);
    }
    free(paths);
}

void
get_gpio_line (const char *gpio_label, struct gpiod_chip **chip, unsigned int *offset)
{
    struct gpiod_line_info *line_info;
    bool has_consumer;

    gpio_line_find (gpio_label, chip, offset);
    if (!*chip) {
        return;
    }

    line_info = gpiod_chip_get_line_info (*chip, *offset);
    if (!line_info) {
        return;
    }

    has_consumer = gpiod_line_info_get_consumer (line_info) != NULL;
    gpiod_line_info_free (line_info);

    if (has_consumer) {
        gpiod_chip_close(*chip);
        *chip = NULL;
        //TODO: warn
    }
}

int
get_gpio_line_value (const char* line_name)
{
    int value;
    struct gpiod_chip *chip;
    unsigned int offset;
    struct gpiod_line_info *line_info;
    struct gpiod_line_settings *line_settings;
    struct gpiod_line_config *line_config;
    struct gpiod_line_request *line_request;
    struct gpiod_request_config *request_config;

    get_gpio_line (line_name, &chip, &offset);
    if (!chip) {
        return E_GPIO_LINE_NOT_FOUND;
    }

    line_info = gpiod_chip_get_line_info (chip, offset);
    if (!line_info) {
        return E_GPIO_LINE_GET_INFO;
    }

    if (gpiod_line_info_get_direction (line_info) != GPIOD_LINE_DIRECTION_OUTPUT) {
        gpiod_line_info_free (line_info);
        return E_GPIO_LINE_NOT_OUTPUT;
    }
    gpiod_line_info_free (line_info);

    line_settings = gpiod_line_settings_new();
    if (!line_settings) {
        return E_GPIO_LINE_SETTINGS;
    }
    gpiod_line_settings_set_direction(line_settings, GPIOD_LINE_DIRECTION_AS_IS);

    line_config = gpiod_line_config_new();
    if (!line_config) {
        gpiod_line_settings_free(line_settings);
        return E_GPIO_LINE_CONFIG;
    }

    if (gpiod_line_config_add_line_settings(line_config, &offset, 1, line_settings) < 0) {
        gpiod_line_config_free(line_config);
        gpiod_line_settings_free(line_settings);
        return E_GPIO_LINE_CONFIGURE;
    }
    gpiod_line_settings_free(line_settings);

    request_config = gpiod_request_config_new();
    if (!request_config) {
        gpiod_line_config_free(line_config);
        return E_GPIO_REQUEST_CONFIG;
    }

    gpiod_request_config_set_consumer(request_config, "ModemManager");

    line_request = gpiod_chip_request_lines(chip, request_config, line_config);

    if (!line_request) {
        gpiod_request_config_free(request_config);
        gpiod_line_config_free(line_config);
        return E_GPIO_LINE_REQUEST;
    }

    value = gpiod_line_request_get_value (line_request, offset);
    gpiod_line_request_release(line_request);
    gpiod_request_config_free(request_config);
    gpiod_line_config_free(line_config);
    if (value == -1) {
        return E_GPIO_LINE_GET_VALUE;
    }
    return value;
}

int
set_gpio_line_value (const char* line_name, int value)
{
    int res;
    struct gpiod_chip *chip;
    unsigned int offset;
    struct gpiod_line_settings *line_settings;
    struct gpiod_line_config *line_config;
    struct gpiod_line_request *line_request;
    struct gpiod_request_config *request_config;

    get_gpio_line (line_name, &chip, &offset);
    if (!chip) {
        return E_GPIO_LINE_NOT_FOUND;
    }

    line_settings = gpiod_line_settings_new();
    if (!line_settings) {
        return E_GPIO_LINE_SETTINGS;
    }
    gpiod_line_settings_set_direction(line_settings, GPIOD_LINE_DIRECTION_OUTPUT);

    line_config = gpiod_line_config_new();
    if (!line_config) {
        gpiod_line_settings_free(line_settings);
        return E_GPIO_LINE_CONFIG;
    }

    if (gpiod_line_config_add_line_settings(line_config, &offset, 1, line_settings) < 0) {
        gpiod_line_config_free(line_config);
        gpiod_line_settings_free(line_settings);
        return E_GPIO_LINE_CONFIGURE;
    }
    gpiod_line_settings_free(line_settings);

    request_config = gpiod_request_config_new();
    if (!request_config) {
        gpiod_line_config_free(line_config);
        return E_GPIO_REQUEST_CONFIG;
    }

    gpiod_request_config_set_consumer(request_config, "ModemManager");

    line_request = gpiod_chip_request_lines(chip, request_config, line_config);

    if (!line_request) {
        gpiod_request_config_free(request_config);
        gpiod_line_config_free(line_config);
        return E_GPIO_LINE_REQUEST;
    }

    res = gpiod_line_request_set_value (line_request, offset, value);
    gpiod_line_request_release(line_request);
    gpiod_request_config_free(request_config);
    gpiod_line_config_free(line_config);
    gpiod_chip_close(chip);
    if (res == -1) {
        return E_GPIO_LINE_SET_VALUE;
    }
    return 0;
}
