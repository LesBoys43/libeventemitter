#pragma once
#include <libeventemitter.h>
// == 函数定义 ==
void EventListener_action_create(EventListener **el, gchar *act,
                                 EventListenerFuncPtr cb);
void EventListener_action_destroy(EventListener **el);
gpointer EventListener_action_call(EventListener **el, GList *args,
                                   gboolean dobtrans, EventEmitter *source_ee);