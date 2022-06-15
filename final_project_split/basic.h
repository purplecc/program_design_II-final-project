#ifndef basic_H
#define basic_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>

#define finish          "\033[0m"
#define light           "\033[01m"
#define black           "\033[30m"
#define B_B_red         "\033[1;31;43m"
#define B_I_green       "\033[1;3;32m"
#define B_U_I_yellow    "\033[1;3;4;33m"
#define B_U_I_green     "\033[1;3;4;32m"
#define B_yellow        "\033[1;33m"
#define blue            "\033[34m"
#define B_purple        "\033[1;35m"
#define B_cyan          "\033[1;36m"
#define B_white         "\033[1;37m"
#define B_BLUE          "\x1B[1;36m"
#define BLUE            "\x1B[0;36m"
#define DBLUE           "\x1B[0;34m"
#define BACK_YELLOW     "\x1B[3;33m"
#define PURPLE          "\x1B[0;35m"
#define B_PURPLE        "\x1B[1;35m"
#define B_I_BA_red      "\033[1;3;2;41m"
#define B_BA_red        "\033[1;2;41m"
#define B_I_BA_green    "\033[1;3;2;42m"
#define red             "\033[41m"
#define Move_the_cursor_up_one      "\e[1A"
#define Move_the_cursor_right_14    "\e[14C"
#define Move_the_cursor_right_11    "\e[11C"
#define Move_the_cursor_left_1      "\e[1D"
#define Clear_one_word              "\e[K"

#endif