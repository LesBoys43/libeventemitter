#include <stdio.h>

#define g_printf printf // g_printf因未知原因无法使用
#define _TOSTRING(str) #str
#define TOSTRING(str) _TOSTRING(str)
#define REALVER TOSTRING(VER)

int main() {
    g_printf("libeventemitter %s\n", REALVER);
    g_printf("This is a free software under BSD-3\n");
}