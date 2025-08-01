#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>
#include <libeventemitter/el.h>

guint EventEmitter_action_deon(EventEmitter **ee, gchar *act) {
    guint c = 0; // 记数
    if (ee == NULL || *ee == NULL || act == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }
    gint i = g_queue_get_length((*ee)->ee_listeners) - 1;
    while (i >= 0) {
        EventListener *curr_el =
            (EventListener *)g_queue_peek_nth((*ee)->ee_listeners, i);
        if (curr_el && g_strcmp0(curr_el->el_listenee, act) == 0) {
            EventListener_action_destroy(&curr_el);
            g_free(curr_el);
            gpointer data = g_queue_peek_nth((*ee)->ee_listeners, i);
            g_queue_remove((*ee)->ee_listeners,
                           data); // g_queue_remove_nth已被移除，因此使用该方法
            c++;
        }
        i--;
    }
    return c;
}