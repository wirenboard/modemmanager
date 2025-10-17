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

#ifndef MM_BROADBAND_MODEM_SIMTECH_GPIO_HELPER_H
#define MM_BROADBAND_MODEM_SIMTECH_GPIO_HELPER_H

#define E_GPIO_LINE_GET_INFO      -1   // can't get gpio line info
#define E_GPIO_LINE_NOT_OUTPUT    -2   // gpio line is not output
#define E_GPIO_LINE_SETTINGS      -3   // can't create gpio line settings
#define E_GPIO_LINE_CONFIG        -4   // can't create gpio line config
#define E_GPIO_LINE_CONFIGURE     -5   // can't configure gpio line
#define E_GPIO_REQUEST_CONFIG     -6   // can't create gpio request config
#define E_GPIO_LINE_REQUEST       -7   // can't request gpio line
#define E_GPIO_LINE_GET_VALUE     -8   // can't get gpio line value
#define E_GPIO_LINE_NOT_FOUND     -9   // can't find gpio line by label
#define E_GPIO_LINE_SET_VALUE     -10  // can't set gpio line value

int get_gpio_line_value (const char* line_name);

int set_gpio_line_value (const char* line_name, int value);

#endif /* MM_BROADBAND_MODEM_SIMTECH_GPIO_HELPER_H */
