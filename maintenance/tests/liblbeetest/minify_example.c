#include "liblbeetest.h"
#include <glib.h>

int main() {
    GList *exampleList = NULL;

    json_value _exampleJson = {.type = JSON_TYPE_STRING,
                               .value = {.string = "hi"}};
    json_value *exampleJson = &_exampleJson;

    LBEE_TestCase exampleCase = {
        .name = "example",
        .code = "#include<stdio.h>\nvoid "
                "main(){printf(\"{\\\"out\\\":\\\"hi\\\"}\");}",
        .extraCflags = "-g",
        .extraLdflags = "-g",
        .excepted = exampleJson};

    exampleList = g_list_append(exampleList, &exampleCase);

    lbeerunall(exampleList);
}