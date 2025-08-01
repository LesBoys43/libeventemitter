#include "internals.h"
#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>
#include <libeventemitter/el.h>

EventEmittingBTData EventEmitter_internals_execEmitting(EventEmitter **ee,
                                                        Event *event) {
    gpointer data = NULL;

    EventListener *el = NULL;

    for (guint i = 0; i < g_queue_get_length((*ee)->ee_listeners); i++) {
        EventListener *curr_el = g_queue_peek_nth((*ee)->ee_listeners, i);
        if (curr_el->el_listenee == event->e_action) {
            if (curr_el->el_once_keep == false) { // 被动清理
                EventListener_action_destroy(&curr_el);
                g_queue_remove((*ee)->ee_listeners, curr_el);
                g_free(curr_el);
                i--; // 保持平衡
                continue;
            }
            data = EventListener_action_call(&curr_el, event->e_args,
                                             event->e_source_ee->ee_do_bwtrans,
                                             event->e_source_ee);
            el = curr_el;
            if (curr_el->el_once) {
                curr_el->el_once_keep = false;
            }
        }
    }

    gboolean shouldNonNull = event->e_source_ee->ee_do_bwtrans;

    EventEmittingBTData eebtd = {.eebtd_who = NULL, .eebtd_what = NULL};

    if (shouldNonNull) {
        eebtd.eebtd_who = el;
        eebtd.eebtd_what = data;
    };

    return eebtd;
}