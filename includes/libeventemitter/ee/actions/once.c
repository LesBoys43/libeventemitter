#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

EventListener *EventEmitter_action_once(EventEmitter **ee, gchar *act,
                                        const EventListenerFuncPtr cb) {
    if (ee == NULL || *ee == NULL || act == NULL || cb == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }
    if (!(*ee)->ee_onable) {
        return NULL;
    }
    EventEmitter_action_on(ee, act, cb); // 复用
    // 标注为once
    EventListener *eld = (EventListener *)g_queue_pop_tail((*ee)->ee_listeners);
    eld->el_once = true;
    g_queue_push_tail((*ee)->ee_listeners, eld);
    return eld;
}