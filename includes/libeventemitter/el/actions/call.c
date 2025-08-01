#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/el.h>

gpointer EventListener_action_call(EventListener **el, GList *args,
                                   gboolean dobtrans, EventEmitter *source_ee) {
    if (el == NULL || *el == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }

    gpointer res = (*el)->el_listener_func(args, dobtrans, source_ee);

    if (dobtrans && res != NULL) {
        return res;
    }

    return NULL;
}