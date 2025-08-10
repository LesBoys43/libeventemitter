#include <glib.h>
#include <glib/gfileutils.h>
#include <json_writer.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

gpointer cb1(GList *dummy1, gboolean dummy2, EventEmitter *dummy3) {
    return "1+1=2";
}

gpointer cb2(GList *dummy1, gboolean dummy2, EventEmitter *dummy3) {
    return "1-1=0";
}

int main(void) {
    EventEmitter *ee = g_malloc(sizeof(EventEmitter));

    GHashTable *cfg = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(cfg, "backwardTransfer", GINT_TO_POINTER(1));

    EventEmitterBackwardTransferPolicy policy = EEBTP_FIRST;
    g_hash_table_insert(cfg, "backwardTransferPolicy", GINT_TO_POINTER(policy));

    EventEmitter_action_create(&ee, cfg);

    EventEmitter_action_on(&ee, "test", cb1);
    EventEmitter_action_on(&ee, "test", cb2);

    gpointer v = (EventEmitter_action_emit(&ee, "test", NULL))
                     .eee_bted_data.eee_bted_data;

    EventEmitter_action_deon(&ee, "test");

    EventEmitter_action_emit(&ee, "test", NULL);

    JsonWriter *jw = jw_open("/tmp/LBEETEST0010.json");

    jw_object_start(jw);
    jw_key(jw, "out");
    jw_string(jw, (gchar *)v);
    jw_object_end(jw);

    jw_close(jw);

    gchar *buf;
    g_file_get_contents("/tmp/LBEETEST0010.json", &buf, NULL, NULL);

    printf("%s", buf);
}