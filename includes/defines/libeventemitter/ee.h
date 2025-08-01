#pragma once
#include <libeventemitter.h>
// == 函数定义 ==
void EventEmitter_action_create(EventEmitter **ee,
                                GHashTable *cfg); // 具体配置参考手册
void EventEmitter_action_destroy(EventEmitter **ee);
EventEmitterEmission
EventEmitter_action_emit(EventEmitter **ee, gchar *act,
                         GList *args); // 每个参数必须是gpointer类型
EventListener *EventEmitter_action_on(EventEmitter **ee, gchar *act,
                                      EventListenerFuncPtr cb);
EventListener *
EventEmitter_action_once(EventEmitter **ee, gchar *act,
                         EventListenerFuncPtr cb); // 相比on，只会被触发一次
guint EventEmitter_action_deon(EventEmitter **ee, gchar *act);
GList *EventEmitter_action_get_control_flags(
    EventEmitter **ee); // 0 emittable 1 onable
void EventEmitter_action_put_control_flags(EventEmitter **ee,
                                           gboolean emittable, gboolean onable);