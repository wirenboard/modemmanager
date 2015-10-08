/*
 * Generated by gdbus-codegen 2.44.1. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __MM_GDBUS_SIM_H__
#define __MM_GDBUS_SIM_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for org.freedesktop.ModemManager1.Sim */

#define MM_GDBUS_TYPE_SIM (mm_gdbus_sim_get_type ())
#define MM_GDBUS_SIM(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MM_GDBUS_TYPE_SIM, MmGdbusSim))
#define MM_GDBUS_IS_SIM(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MM_GDBUS_TYPE_SIM))
#define MM_GDBUS_SIM_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), MM_GDBUS_TYPE_SIM, MmGdbusSimIface))

struct _MmGdbusSim;
typedef struct _MmGdbusSim MmGdbusSim;
typedef struct _MmGdbusSimIface MmGdbusSimIface;

struct _MmGdbusSimIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_change_pin) (
    MmGdbusSim *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_old_pin,
    const gchar *arg_new_pin);

  gboolean (*handle_enable_pin) (
    MmGdbusSim *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_pin,
    gboolean arg_enabled);

  gboolean (*handle_send_pin) (
    MmGdbusSim *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_pin);

  gboolean (*handle_send_puk) (
    MmGdbusSim *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_puk,
    const gchar *arg_pin);

  const gchar * (*get_imsi) (MmGdbusSim *object);

  const gchar * (*get_operator_identifier) (MmGdbusSim *object);

  const gchar * (*get_operator_name) (MmGdbusSim *object);

  const gchar * (*get_sim_identifier) (MmGdbusSim *object);

};

GType mm_gdbus_sim_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *mm_gdbus_sim_interface_info (void);
guint mm_gdbus_sim_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void mm_gdbus_sim_complete_send_pin (
    MmGdbusSim *object,
    GDBusMethodInvocation *invocation);

void mm_gdbus_sim_complete_send_puk (
    MmGdbusSim *object,
    GDBusMethodInvocation *invocation);

void mm_gdbus_sim_complete_enable_pin (
    MmGdbusSim *object,
    GDBusMethodInvocation *invocation);

void mm_gdbus_sim_complete_change_pin (
    MmGdbusSim *object,
    GDBusMethodInvocation *invocation);



/* D-Bus method calls: */
void mm_gdbus_sim_call_send_pin (
    MmGdbusSim *proxy,
    const gchar *arg_pin,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean mm_gdbus_sim_call_send_pin_finish (
    MmGdbusSim *proxy,
    GAsyncResult *res,
    GError **error);

gboolean mm_gdbus_sim_call_send_pin_sync (
    MmGdbusSim *proxy,
    const gchar *arg_pin,
    GCancellable *cancellable,
    GError **error);

void mm_gdbus_sim_call_send_puk (
    MmGdbusSim *proxy,
    const gchar *arg_puk,
    const gchar *arg_pin,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean mm_gdbus_sim_call_send_puk_finish (
    MmGdbusSim *proxy,
    GAsyncResult *res,
    GError **error);

gboolean mm_gdbus_sim_call_send_puk_sync (
    MmGdbusSim *proxy,
    const gchar *arg_puk,
    const gchar *arg_pin,
    GCancellable *cancellable,
    GError **error);

void mm_gdbus_sim_call_enable_pin (
    MmGdbusSim *proxy,
    const gchar *arg_pin,
    gboolean arg_enabled,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean mm_gdbus_sim_call_enable_pin_finish (
    MmGdbusSim *proxy,
    GAsyncResult *res,
    GError **error);

gboolean mm_gdbus_sim_call_enable_pin_sync (
    MmGdbusSim *proxy,
    const gchar *arg_pin,
    gboolean arg_enabled,
    GCancellable *cancellable,
    GError **error);

void mm_gdbus_sim_call_change_pin (
    MmGdbusSim *proxy,
    const gchar *arg_old_pin,
    const gchar *arg_new_pin,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean mm_gdbus_sim_call_change_pin_finish (
    MmGdbusSim *proxy,
    GAsyncResult *res,
    GError **error);

gboolean mm_gdbus_sim_call_change_pin_sync (
    MmGdbusSim *proxy,
    const gchar *arg_old_pin,
    const gchar *arg_new_pin,
    GCancellable *cancellable,
    GError **error);



/* D-Bus property accessors: */
const gchar *mm_gdbus_sim_get_sim_identifier (MmGdbusSim *object);
gchar *mm_gdbus_sim_dup_sim_identifier (MmGdbusSim *object);
void mm_gdbus_sim_set_sim_identifier (MmGdbusSim *object, const gchar *value);

const gchar *mm_gdbus_sim_get_imsi (MmGdbusSim *object);
gchar *mm_gdbus_sim_dup_imsi (MmGdbusSim *object);
void mm_gdbus_sim_set_imsi (MmGdbusSim *object, const gchar *value);

const gchar *mm_gdbus_sim_get_operator_identifier (MmGdbusSim *object);
gchar *mm_gdbus_sim_dup_operator_identifier (MmGdbusSim *object);
void mm_gdbus_sim_set_operator_identifier (MmGdbusSim *object, const gchar *value);

const gchar *mm_gdbus_sim_get_operator_name (MmGdbusSim *object);
gchar *mm_gdbus_sim_dup_operator_name (MmGdbusSim *object);
void mm_gdbus_sim_set_operator_name (MmGdbusSim *object, const gchar *value);


/* ---- */

#define MM_GDBUS_TYPE_SIM_PROXY (mm_gdbus_sim_proxy_get_type ())
#define MM_GDBUS_SIM_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MM_GDBUS_TYPE_SIM_PROXY, MmGdbusSimProxy))
#define MM_GDBUS_SIM_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MM_GDBUS_TYPE_SIM_PROXY, MmGdbusSimProxyClass))
#define MM_GDBUS_SIM_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MM_GDBUS_TYPE_SIM_PROXY, MmGdbusSimProxyClass))
#define MM_GDBUS_IS_SIM_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MM_GDBUS_TYPE_SIM_PROXY))
#define MM_GDBUS_IS_SIM_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MM_GDBUS_TYPE_SIM_PROXY))

typedef struct _MmGdbusSimProxy MmGdbusSimProxy;
typedef struct _MmGdbusSimProxyClass MmGdbusSimProxyClass;
typedef struct _MmGdbusSimProxyPrivate MmGdbusSimProxyPrivate;

struct _MmGdbusSimProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  MmGdbusSimProxyPrivate *priv;
};

struct _MmGdbusSimProxyClass
{
  GDBusProxyClass parent_class;
};

GType mm_gdbus_sim_proxy_get_type (void) G_GNUC_CONST;

void mm_gdbus_sim_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
MmGdbusSim *mm_gdbus_sim_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
MmGdbusSim *mm_gdbus_sim_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void mm_gdbus_sim_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
MmGdbusSim *mm_gdbus_sim_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
MmGdbusSim *mm_gdbus_sim_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define MM_GDBUS_TYPE_SIM_SKELETON (mm_gdbus_sim_skeleton_get_type ())
#define MM_GDBUS_SIM_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MM_GDBUS_TYPE_SIM_SKELETON, MmGdbusSimSkeleton))
#define MM_GDBUS_SIM_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MM_GDBUS_TYPE_SIM_SKELETON, MmGdbusSimSkeletonClass))
#define MM_GDBUS_SIM_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MM_GDBUS_TYPE_SIM_SKELETON, MmGdbusSimSkeletonClass))
#define MM_GDBUS_IS_SIM_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MM_GDBUS_TYPE_SIM_SKELETON))
#define MM_GDBUS_IS_SIM_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MM_GDBUS_TYPE_SIM_SKELETON))

typedef struct _MmGdbusSimSkeleton MmGdbusSimSkeleton;
typedef struct _MmGdbusSimSkeletonClass MmGdbusSimSkeletonClass;
typedef struct _MmGdbusSimSkeletonPrivate MmGdbusSimSkeletonPrivate;

struct _MmGdbusSimSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  MmGdbusSimSkeletonPrivate *priv;
};

struct _MmGdbusSimSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType mm_gdbus_sim_skeleton_get_type (void) G_GNUC_CONST;

MmGdbusSim *mm_gdbus_sim_skeleton_new (void);


G_END_DECLS

#endif /* __MM_GDBUS_SIM_H__ */
