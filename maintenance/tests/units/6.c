#include <glib.h>
#include <glib/gfileutils.h>
#include <json_writer.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

guint globalCounter = 0;

gpointer cb(GList *dummy1, gboolean dummy2, EventEmitter *dummy3) {
    globalCounter++;
}

int main(void) {
    EventEmitter *ee = g_malloc(sizeof(EventEmitter));

    EventEmitter_action_create(&ee, g_hash_table_new(g_str_hash, g_str_equal));

    EventEmitter_action_on(&ee, "test", cb);
    EventEmitter_action_on(&ee, "test", cb);

    EventEmitter_action_emit(&ee, "test", NULL);

    EventEmitter_action_deon(&ee, "test");

    EventEmitter_action_emit(&ee, "test", NULL);

    JsonWriter *jw = jw_open("/tmp/LBEETEST0006.json");

    jw_object_start(jw);
    jw_key(jw, "out");
    jw_string(jw, g_strdup_printf("%u", globalCounter));
    jw_object_end(jw);

    jw_close(jw);

    gchar *buf;
    g_file_get_contents("/tmp/LBEETEST0006.json", &buf, NULL, NULL);

    printf("%s", buf);
}