#include "liblbeetest.h"
#include "depends/libHarryDCjson/json.h"
#include <glib.h>
#include <glib/gfileutils.h>
#include <glib/gstdio.h>
#include <libeventemitter.h>

gboolean fail = 0;

void lbeerunone(LBEE_TestCase *testcase, gpointer user_data) {
    gchar *template = g_strdup("/tmp/LBEETEST_XXXXXX");
    const gchar *tmp;

    tmp = g_strdup(g_mkdtemp_full(template, 0700));

    g_free(template);

    gchar *pathbuf = g_build_path(
        G_DIR_SEPARATOR_S, tmp,
        g_strconcat("LBEETest_", testcase->name, ".c", NULL), NULL);

    g_file_set_contents(pathbuf, testcase->code,
                        g_utf8_strlen(testcase->code, -1), NULL);

    /*gchar *gccArg = g_malloc(480);
    snprintf(gccArg, 480, "-I%s -L%s %s %s %s %s -o %s %s",
             LBEE_Test_LibeeIncludeDir, LBEE_Test_LibeeLibDir,
             LBEE_Test_DefaultCflags, LBEE_Test_DefaultLdflags,
             testcase->extraCflags, testcase->extraLdflags,
             g_build_path(G_DIR_SEPARATOR_S, tmp,
                          g_strconcat("LBEETest_", testcase->name, NULL), NULL),
             g_build_path(G_DIR_SEPARATOR_S, tmp,
                          g_strconcat("LBEETest_", testcase->name, ".c", NULL),
                          NULL));*/

    gchar *argv[] = {
        g_build_path(G_DIR_SEPARATOR_S, "/usr", "bin", "gcc", NULL),
        g_strdup_printf("-I%s", LBEE_Test_LibeeIncludeDir),
        g_strdup_printf("-L%s", LBEE_Test_LibeeLibDir),
        g_build_path(G_DIR_SEPARATOR_S, tmp,
                     g_strconcat("LBEETest_", testcase->name, ".c", NULL),
                     NULL),
        LBEE_Test_DefaultCflags,
        LBEE_Test_DefaultLdflags,
        testcase->extraCflags,
        testcase->extraLdflags,
        "-o",
        g_build_path(G_DIR_SEPARATOR_S, tmp,
                     g_strconcat("LBEETest_", testcase->name, NULL), NULL),
        NULL};

    gint status = 0;

    gchar *cc_stderr;

    g_spawn_sync(tmp, argv, NULL, 8, NULL, NULL, NULL, &cc_stderr, &status,
                 NULL);

    // g_free(gccArg);

    if (status != 0 ||
        !g_file_test(
            g_build_path(G_DIR_SEPARATOR_S, tmp,
                         g_strconcat("LBEETest_", testcase->name, NULL), NULL),
            G_FILE_TEST_EXISTS)) {

        printf("CC Stderr: %s\n", cc_stderr);
        g_unlink(g_build_path(G_DIR_SEPARATOR_S, tmp,
                              g_strconcat("LBEETest_", testcase->name, NULL),
                              ".c", NULL));
        g_rmdir(tmp);
        lbeeformatout(testcase->name, 0);
        return;
    }

    gchar *tca[] = {g_build_path(G_DIR_SEPARATOR_S, tmp,
                                 g_strconcat("LBEETest_", testcase->name, NULL),
                                 NULL),
                    NULL};

    gchar *out;

    g_spawn_sync(tmp, tca, NULL, 16, NULL, NULL, &out, NULL, NULL, NULL);

    json_value root;

    // printf("%s\n", out);

    json_parse(out, &root);

    json_value *actual = json_value_with_key(&root, "out");

    g_unlink(g_build_path(G_DIR_SEPARATOR_S, tmp,
                          g_strconcat("LBEETest_", testcase->name, NULL), ".c",
                          NULL));
    g_unlink(g_build_path(G_DIR_SEPARATOR_S, tmp,
                          g_strconcat("LBEETest_", testcase->name, NULL),
                          NULL));

    g_rmdir(tmp);

    if (g_strcmp0(json_value_to_string(actual),
                  json_value_to_string(testcase->excepted)) == 0) {
        lbeeformatout(testcase->name, 1);
        return;
    } else {
        lbeeformatout(testcase->name, 0);
        return;
    }
}

guint lbeerunall(GList *list) {
    g_list_foreach(list, (GFunc)lbeerunone, NULL);
    return fail;
}

void lbeeformatout(gchar *name, gboolean ok) {
    if (!ok) {
        fail++;
    }

    gchar *okstr = ok ? "PASS" : "FAIL";

    printf(LBEE_Test_OutFormat, name, okstr);
}