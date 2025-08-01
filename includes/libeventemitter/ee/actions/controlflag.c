#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

GList *EventEmitter_action_get_control_flags(EventEmitter **ee) {
    if (ee == NULL || *ee == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }

    GList *gl = NULL;

    gl = g_list_append(gl, GINT_TO_POINTER((*ee)->ee_emitable));
    gl = g_list_append(gl, GINT_TO_POINTER((*ee)->ee_onable));

    return gl;
}

void EventEmitter_action_put_control_flags(EventEmitter **ee,
                                           gboolean emittable,
                                           gboolean onable) {
    if (ee == NULL || *ee == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }

    (*ee)->ee_emitable = emittable;
    (*ee)->ee_onable = onable;
}