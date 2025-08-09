#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

// == 基础行为实现 ==
void EventEmitter_action_create(EventEmitter **ee, GHashTable *cfg) {
    if (ee == NULL || *ee == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }
    (*ee)->ee_listeners = g_queue_new();
    (*ee)->ee_emitable = true;
    (*ee)->ee_onable = true;
    (*ee)->ee_listener_count = 0;
    if (g_hash_table_contains(cfg, "backwardTransfer")) {
        (*ee)->ee_do_bwtrans = (gboolean)GPOINTER_TO_INT(
            g_hash_table_lookup(cfg, "backwardTransfer"));
    } else {
        (*ee)->ee_do_bwtrans = false; // 默认不做反向传输
    }

    if (g_hash_table_contains(cfg, "backwardTransferPolicy")) {
        (*ee)->ee_btpolicy = (EventEmitterBackwardTransferPolicy)GPOINTER_TO_INT(
            g_hash_table_lookup(cfg, "backwardTransferPolicy"))
    } else {
        // 使用默认策略
        (*ee)->ee_btpolicy = EEBTP_DEFAULT;
    }
    return;
}

void EventEmitter_action_destroy(EventEmitter **ee) {
    if (ee == NULL || *ee == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }
    g_queue_free_full((*ee)->ee_listeners, (GDestroyNotify)g_free);
    // 你也许需要：
    /*g_free(*ee);
    g_free(ee);*/
}