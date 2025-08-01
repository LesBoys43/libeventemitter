#pragma once
#include <libeventemitter.h>
// == 函数定义 ==
void Event_action_create(Event **e, gchar *act, GList *args,
                         EventEmitter *source_ee);
void Event_action_destroy(Event **e);