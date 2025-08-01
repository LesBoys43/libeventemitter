#include <glib.h>
#include <glib/gfileutils.h>
#include <json_writer.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

gpointer cb(GList *dummy1, gboolean dummy2, EventEmitter *dummy3) {
    return (gpointer)0x1440;
}

int main(void) {
    EventEmitter *ee = g_malloc(sizeof(EventEmitter));

    GHashTable *cfg = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(cfg, "backwardTransfer", GINT_TO_POINTER(1));

    EventEmitter_action_create(&ee, cfg);

    EventEmitter_action_on(&ee, "test", cb);

    gpointer v = (EventEmitter_action_emit(&ee, "test", NULL))
                     .eee_bted_data.eee_bted_data;

    JsonWriter *jw = jw_open("/tmp/LBEETEST0004.json");

    jw_object_start(jw);
    jw_key(jw, "out");
    if (v == NULL) {
        jw_string(jw, "isnull");
    } else {
        jw_string(jw, "isnotnull");
    }
    jw_object_end(jw);

    jw_close(jw);

    gchar *buf;
    g_file_get_contents("/tmp/LBEETEST0004.json", &buf, NULL, NULL);

    printf("%s", buf);
}