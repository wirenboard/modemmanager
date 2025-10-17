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
 * Copyright (C) 2023 Wiren Board
 */

#ifndef MM_SMS_SIMTECH_A7600_H
#define MM_SMS_SIMTECH_A7600_H

#include <glib.h>
#include <glib-object.h>

#define _LIBMM_INSIDE_MM
#include <libmm-glib.h>

#include "mm-base-sms.h"

#define MM_TYPE_SMS_SIMTECH_A7600            (mm_sms_simtech_a7600_get_type ())
#define MM_SMS_SIMTECH_A7600(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MM_TYPE_SMS_SIMTECH_A7600, MMSmsSimtechA7600))
#define MM_SMS_SIMTECH_A7600_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  MM_TYPE_SMS_SIMTECH_A7600, MMSmsSimtechA7600Class))
#define MM_IS_SMS_SIMTECH_A7600(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MM_TYPE_SMS_SIMTECH_A7600))
#define MM_IS_SMS_SIMTECH_A7600_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  MM_TYPE_SMS_SIMTECH_A7600))
#define MM_SMS_SIMTECH_A7600_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  MM_TYPE_SMS_SIMTECH_A7600, MMSmsSimtechA7600Class))

typedef struct _MMSmsSimtechA7600 MMSmsSimtechA7600;
typedef struct _MMSmsSimtechA7600Class MMSmsSimtechA7600Class;

struct _MMSmsSimtechA7600 {
    MMBaseSms parent;
};

struct _MMSmsSimtechA7600Class {
    MMBaseSmsClass parent;
};

GType mm_sms_simtech_a7600_get_type (void);
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MMSmsSimtechA7600, g_object_unref)

MMBaseSms *mm_sms_simtech_a7600_new (MMBaseModem *modem);

#endif /* MM_SMS_SIMTECH_A7600_H */
