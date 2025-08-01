#include <glib.h>
#include <glib/gfileutils.h>
#include <json_writer.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

gpointer cb(GList *args, gboolean dummy1, EventEmitter *dummy2) {
    JsonWriter *jw = jw_open("/tmp/LBEETEST0001.json");

    jw_object_start(jw);
    jw_key(jw, "out");
    jw_string(jw, (gchar *)g_list_nth_data(args, 0));
    jw_object_end(jw);

    jw_close(jw);

    gchar *buf;
    g_file_get_contents("/tmp/LBEETEST0001.json", &buf, NULL, NULL);

    printf("%s", buf);
}

int main(void) {
    EventEmitter *ee = g_malloc(sizeof(EventEmitter));

    EventEmitter_action_create(&ee, g_hash_table_new(g_str_hash, g_str_equal));

    EventEmitter_action_on(&ee, "test", cb);

    GList *args = NULL;
    args = g_list_append(args, "HelloWorld");

    EventEmitter_action_emit(&ee, "test", args);
}