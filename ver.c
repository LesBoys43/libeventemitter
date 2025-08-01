#include <stdio.h>

#define g_printf printf // g_printf因未知原因无法使用

int main() {
    g_printf("libeventemitter %f\n", VER);
    g_printf("This is a free software under BSD-3\n");
}