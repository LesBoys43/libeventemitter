#include <glib.h>
#include <glib/gfileutils.h>
#include <json_writer.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

int main(void) {
    EventEmitter *ee = g_malloc(sizeof(EventEmitter));

    EventEmitter_action_create(&ee, g_hash_table_new(g_str_hash, g_str_equal));

    EventEmitter_action_put_control_flags(&ee, 1, 1);

    GList *x = EventEmitter_action_get_control_flags(&ee);

    guint a = GPOINTER_TO_INT(g_list_nth_data(x, 1));
    guint b = GPOINTER_TO_INT(g_list_nth_data(x, 0));

    JsonWriter *jw = jw_open("/tmp/LBEETEST0009.json");

    jw_object_start(jw);
    jw_key(jw, "out");
    jw_string(jw, g_strdup_printf("%u", a + b));
    jw_object_end(jw);

    jw_close(jw);

    gchar *buf;
    g_file_get_contents("/tmp/LBEETEST0009.json", &buf, NULL, NULL);

    printf("%s", buf);
}