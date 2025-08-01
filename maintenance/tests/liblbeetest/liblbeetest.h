#include "depends/libHarryDCjson/json.h"
#include <glib.h>
#include <libeventemitter.h>

#ifdef LBEESELF
#define LBEE_Test_OutFormat "+%s+ -- %s\n"

#define LBEE_Test_DefaultCflags                                                \
    "-g", "-O2", "-rdynamic", "-I/usr/include/glib-2.0",                       \
        "-I/usr/lib/glib-2.0/include", "-I/usr/include/sysprof-6", "-pthread", "/usr/lib/x86_64-linux-gnu/glib-2.0/include"
#define LBEE_Test_DefaultLdflags "-g", "-lee", "-ljsonwriter", "-lglib-2.0"

#ifndef LBEE_Test_LibeeIncludeDir
#error "A critical marco is undefined"
#endif
#ifndef LBEE_Test_LibeeLibDir
#error "A critical marco is undefined"
#endif
#endif

typedef struct LBEE_TestCase {
    gchar *code;
    gchar *name;
    gchar *extraCflags;
    gchar *extraLdflags;
    json_value *excepted;
} LBEE_TestCase;

void lbeerunall(GList *list);
void lbeerunone(LBEE_TestCase *testcase, gpointer user_data);
void lbeeformatout(gchar *name, gboolean ok);
