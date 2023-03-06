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
 * Copyright (C) 2023 Wiren Board
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include <ModemManager.h>
#define _LIBMM_INSIDE_MM
#include <libmm-glib.h>

#include "mm-iface-modem.h"
#include "mm-iface-modem-messaging.h"
#include "mm-sms-simtech-a7600.h"
#include "mm-base-modem.h"
#include "mm-log-object.h"

G_DEFINE_TYPE (MMSmsSimtechA7600, mm_sms_simtech_a7600, MM_TYPE_BASE_SMS)


/*****************************************************************************/
/* Send the SMS */

typedef struct {
    gboolean send_ok;
    GError* error;
} MMSimtechA7600SendSmsContext;

static gboolean
sms_simtech_a7600_send_finish (MMBaseSms *self,
                               GAsyncResult *res,
                               GError **error)
{
    return g_task_propagate_boolean (G_TASK (res), error);
}

static void
mm_sms_simtech_a7600_ucs2_charset_ready (MMIfaceModem *self,
                                         GAsyncResult *res,
                                         GTask *task)
{
    GError *error = NULL;
    MMSimtechA7600SendSmsContext* ctx;

    ctx = g_task_get_task_data (task);

    if (!MM_IFACE_MODEM_GET_INTERFACE (self)->setup_charset_finish (self, res, &error)) {
        mm_obj_dbg (self, "couldn't set charset UCS2: %s",
                    error->message);
        g_error_free (error);
    }

    if (ctx->send_ok) {
        g_task_return_boolean(task, TRUE);
    } else {
        g_task_return_error (task, ctx->error);
    } 
    g_object_unref (task);
}

static void
mm_sms_simtech_a7600_send_sms_ready (MMBaseSms *self,
                                     GAsyncResult *res,
                                     GTask *task)
{
    MMBaseModem *modem;
    MMSimtechA7600SendSmsContext* ctx;

    ctx = g_task_get_task_data (task);

    ctx->send_ok = MM_BASE_SMS_CLASS (mm_sms_simtech_a7600_parent_class)->send_finish(self, res, &ctx->error);

    g_object_get (self, MM_BASE_SMS_MODEM, &modem, NULL);

    MM_IFACE_MODEM_GET_INTERFACE (modem)->setup_charset (
        MM_IFACE_MODEM (modem),
        MM_MODEM_CHARSET_UCS2,
        (GAsyncReadyCallback)mm_sms_simtech_a7600_ucs2_charset_ready,
        task);
}

static void
mm_sms_simtech_a7600_gsm_charset_ready (MMIfaceModem *self,
                                        GAsyncResult *res,
                                        GTask *task)
{
    GError *error = NULL;
    MMBaseSms *sms;

    if (!MM_IFACE_MODEM_GET_INTERFACE (self)->setup_charset_finish (self, res, &error)) {
        mm_obj_dbg (self, "couldn't set charset GSM: %s",
                    error->message);
        g_task_return_error (task, error);
        g_object_unref (task);
        return;
    }

    sms = g_task_get_source_object (task);
    MM_BASE_SMS_CLASS (mm_sms_simtech_a7600_parent_class)->send(
        sms,
        (GAsyncReadyCallback)mm_sms_simtech_a7600_send_sms_ready,
        task);
}

static void
sms_simtech_a7600_send (MMBaseSms *self,
          GAsyncReadyCallback callback,
          gpointer user_data)
{
    MMBaseModem *modem;
    GTask *task;
    MMSimtechA7600SendSmsContext* ctx;

    task = g_task_new (self, NULL, callback, user_data);
    ctx = g_new (MMSimtechA7600SendSmsContext, 1);
    ctx->send_ok = FALSE;
    ctx->error = NULL;
    g_task_set_task_data (task, ctx, g_free);

    g_object_get (self, MM_BASE_SMS_MODEM, &modem, NULL);

    MM_IFACE_MODEM_GET_INTERFACE (modem)->setup_charset (
        MM_IFACE_MODEM (modem),
        MM_MODEM_CHARSET_GSM,
        (GAsyncReadyCallback)mm_sms_simtech_a7600_gsm_charset_ready,
        task);
}

/*****************************************************************************/

MMBaseSms *
mm_sms_simtech_a7600_new (MMBaseModem *modem)
{
    return MM_BASE_SMS (g_object_new (MM_TYPE_SMS_SIMTECH_A7600,
                                      MM_BASE_SMS_MODEM, modem,
                                      NULL));
}

static void
mm_sms_simtech_a7600_init (MMSmsSimtechA7600 *self)
{
}

static void
mm_sms_simtech_a7600_class_init (MMSmsSimtechA7600Class *klass)
{
    MMBaseSmsClass *base_sms_class = MM_BASE_SMS_CLASS (klass);

    base_sms_class->send = sms_simtech_a7600_send;
    base_sms_class->send_finish = sms_simtech_a7600_send_finish;
}
