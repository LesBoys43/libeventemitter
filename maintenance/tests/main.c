#include "liblbeetest/depends/libHarryDCjson/json.h"
#include "liblbeetest/liblbeetest.h"
#include <glib.h>
#include <glib/gfileutils.h>

#define max 2

int main() {
    GList *list = NULL;

    // 第一个测试用例
    gchar *code1 = NULL;
    g_file_get_contents("units/1.c", &code1, NULL, NULL);

    json_value exceptedjv1 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "HelloWorld"}};

    LBEE_TestCase tc1 = {
        .name = "Basic listen event and emit message - Should trigger callback",
        .code = code1,
        .excepted = &exceptedjv1,
        .extraCflags = "-O0",
        .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc1);

    // 第二个测试用例
    gchar *code2 = NULL;
    g_file_get_contents("units/2.c", &code2, NULL, NULL);

    json_value exceptedjv2 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "1"}};

    LBEE_TestCase tc2 = {.name = "Try emit message after deon event listeners "
                                 "- Should not trigger callback",
                         .code = code2,
                         .excepted = &exceptedjv2,
                         .extraCflags = "-O0",
                         .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc2);

    // 第三个测试用例
    gchar *code3 = NULL;
    g_file_get_contents("units/3.c", &code3, NULL, NULL);

    json_value exceptedjv3 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "isnull"}};

    LBEE_TestCase tc3 = {
        .name = "Check return value of emit when Backward Transfer is disabled "
                "- Return value should be null",
        .code = code3,
        .excepted = &exceptedjv3,
        .extraCflags = "-O0",
        .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc3);

    // 第四个测试用例
    gchar *code4 = NULL;
    g_file_get_contents("units/4.c", &code4, NULL, NULL);

    json_value exceptedjv4 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "isnotnull"}};

    LBEE_TestCase tc4 = {
        .name = "Check return value of emit when Backward Transfer is enabled "
                "- Return value should be not-null",
        .code = code4,
        .excepted = &exceptedjv4,
        .extraCflags = "-O0",
        .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc4);

    // 第二个测试用例
    gchar *code5 = NULL;
    g_file_get_contents("units/5.c", &code5, NULL, NULL);

    json_value exceptedjv5 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "1"}};

    LBEE_TestCase tc5 = {.name = "Try emit 2 messages to an once listener - "
                                 "Should only trigger one time",
                         .code = code5,
                         .excepted = &exceptedjv5,
                         .extraCflags = "-O0",
                         .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc5);

    // 第六个测试用例
    gchar *code6 = NULL;
    g_file_get_contents("units/6.c", &code6, NULL, NULL);

    json_value exceptedjv6 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "2"}};

    LBEE_TestCase tc6 = {.name = "Deon an event listenened by multi listeners "
                                 "- All listeners should got removed",
                         .code = code6,
                         .excepted = &exceptedjv6,
                         .extraCflags = "-O0",
                         .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc6);

    // 第四个测试用例
    gchar *code7 = NULL;
    g_file_get_contents("units/7.c", &code7, NULL, NULL);

    json_value exceptedjv7 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "1-1=0"}};

    LBEE_TestCase tc7 = {.name =
                             "Check backward transfer return value when multi "
                             "listeners listened this event - Return value "
                             "should be the return value of last listener",
                         .code = code7,
                         .excepted = &exceptedjv7,
                         .extraCflags = "-O0",
                         .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc7);

    // 第四个测试用例
    gchar *code8 = NULL;
    g_file_get_contents("units/8.c", &code8, NULL, NULL);

    json_value exceptedjv8 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "1"}};

    LBEE_TestCase tc8 = {.name = "Try emit or on when the control flag is zero "
                                 "- The action should not do actually",
                         .code = code8,
                         .excepted = &exceptedjv8,
                         .extraCflags = "-O0",
                         .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc8);

    // 第四个测试用例
    gchar *code9 = NULL;
    g_file_get_contents("units/9.c", &code9, NULL, NULL);

    json_value exceptedjv9 = {.type = JSON_TYPE_STRING,
                              .value = {.string = "2"}};

    LBEE_TestCase tc9 = {.name =
                             "Get the control flags we set before - The return "
                             "value should equals to the value we set before",
                         .code = code9,
                         .excepted = &exceptedjv9,
                         .extraCflags = "-O0",
                         .extraLdflags = "-ljsonwriter"};

    list = g_list_append(list, &tc9);

    // 运行所有测试
    lbeerunall(list);

    // 清理资源
    g_free(code1);
    g_free(code2);
    g_free(code3);
    g_free(code4);
    g_free(code5);
    g_free(code6);
    g_free(code7);
    g_free(code8);
    g_free(code9);
}