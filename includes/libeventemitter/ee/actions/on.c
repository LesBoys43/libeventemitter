#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>
#include <libeventemitter/el.h>

EventListener *EventEmitter_action_on(EventEmitter **ee, gchar *act,
                                      const EventListenerFuncPtr cb) {
    if (ee == NULL || *ee == NULL || act == NULL || cb == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }
    if (!(*ee)->ee_onable) {
        return NULL;
    }
    EventListener *el = g_malloc(sizeof(EventListener));
    EventListener_action_create(&el, act, cb);
    g_queue_push_tail((*ee)->ee_listeners, el);
    return el;
};