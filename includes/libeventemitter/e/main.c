#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/el.h>

void Event_action_create(Event **e, gchar *act, GList *args,
                         EventEmitter *source_ee) {
    if (e == NULL || *e == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }

    (*e)->e_action = act;
    (*e)->e_args = args;
    (*e)->e_source_ee = source_ee;

    return;
}

void Event_action_destroy(Event **e) {
    if (e == NULL || *e == NULL) { // 我不认为这有意义 但为了一致性 还是加上吧
        LIBEE_FATALERROR_NULLPTR;
    }
    // 为确保配套 我们不执行任何操作
}