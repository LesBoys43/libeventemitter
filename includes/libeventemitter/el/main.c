#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/el.h>

void EventListener_action_create(EventListener **el, gchar *act,
                                 EventListenerFuncPtr cb) {
    if (el == NULL || *el == NULL || act == NULL || cb == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }
    (*el)->el_listenee = act;
    (*el)->el_listener_func = cb;
    (*el)->el_once = false;
    (*el)->el_once_keep = true;
    return;
}

void EventListener_action_destroy(EventListener **el) {
    if (el == NULL || *el == NULL) { // 我不认为这有意义 但为了一致性 还是加上吧
        LIBEE_FATALERROR_NULLPTR;
    }
    // 为确保配套 我们不执行任何操作
}