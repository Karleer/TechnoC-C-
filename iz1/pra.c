/*
АПО-13
Русакова Мария

Задача A-7. Задача о скобочной последовательности

Time limit:	14 s

Memory limit:	64 M

Составить программу построчной обработки текста. Суть обработки - отбор строк, содержащих одинаковое количество открывающих и закрывающих круглых скобок. 

Программа считывает входные данные со стандартного ввода, и печатает результат в стандартный вывод. 

Процедура отбора нужных строк должна быть оформлена в виде отдельной функции, которой на вход подается массив строк (который необходимо обработать), количество переданных строк, а также указатель на переменную, в которой необходимо разместить результат - массив отобранных строк. 

В качестве возвращаемого значения функция должна возвращать количество строк, содержащихся в результирующем массиве. 

Программа должна уметь обрабатывать ошибки - такие как неверные входные данные(отсутствие входных строк) или ошибки выделения памяти и т.п.

В случае возникновения ошибки нужно выводить об этом сообщение "[error]" и завершать выполнение программы. 

ВАЖНО! Программа в любом случае должна возвращать 0. Не пишите return -1, exit(1) и т.п. Даже если обнаружилась какая-то ошибка, все равно необходимо вернуть 0! (и напечатать [error] в stdout).

*/







#define _POSIX_C_SOURCE 200809L

#define _GNU_SOURCE

#include "stdio.h"

#include <stdlib.h>

#include <string.h>





char** StrFilt(char** str, int num_lines, int* num_of_correct_strs){

    char **out_of_str = (char **)malloc(num_lines*sizeof(char*));

    *num_of_correct_strs = 0;

    int count_simb = 0;

    for (int y = 0; y < num_lines; y++) {

        int count = 0;

        if (strcmp(str[y], "\n")) {

            int i = 0;

            for (; i < strlen(*(str + y)); i++) {

                

                if (str[y][i] == '(') {

                    count++;

                }

                if (str[y][i] == ')') {

                    count--;

                }

                if (count < 0) { 

                    break;

                }

            }

            count_simb += i;

            if (count == 0) {

                memcpy(&out_of_str[(*num_of_correct_strs)], &(str[y]), sizeof(str[y]));


                (*num_of_correct_strs)++;

            }

        }

    }

    out_of_str = (char**) realloc(out_of_str, *num_of_correct_strs*count_simb*sizeof(char));

    return out_of_str;

}

int main(int argc, const char * argv[]) {

    int len_of_str = 2;

    int num_of_strs = 1;

    int log_num_of_strs = 0;

    char** strs =  (char**) malloc(num_of_strs*sizeof(char*));



    char *str = (char*)malloc(len_of_str*sizeof(char));

    str[0]='\0';

    char simbl;

    int count_strs = 0;

    int number_of_symbol = 0; //Счетчик символов в строке



    while ((simbl = getchar()) != EOF) {

        if (simbl == '\n') {

            if (number_of_symbol == 0) {

                if (number_of_symbol+1 >= len_of_str) {

                    str = (char*)realloc(str, (len_of_str+=2) * sizeof(char));

                }

                str[number_of_symbol++] = simbl;

                str[number_of_symbol] = '\0';

                continue;

            }

            if (log_num_of_strs >= num_of_strs) {

                strs = (char**)realloc(strs, ++num_of_strs * sizeof(char*));

            }

            strs[log_num_of_strs++] = str;

            str = (char*)malloc(len_of_str*sizeof(char));

            str[0] = '\0';

            ++count_strs;

            number_of_symbol = 0;

            continue;

        }

        if (number_of_symbol+1 >= len_of_str) {

            str = (char*)realloc(str, (len_of_str+=2) * sizeof(char));

        }

        str[number_of_symbol++] = simbl;

        str[number_of_symbol] = '\0';

    }

    if (number_of_symbol != 0) {

        if (log_num_of_strs >= num_of_strs) {

            strs = (char**)realloc(strs, ++num_of_strs * sizeof(char*));

        }

        strs[log_num_of_strs] = str;

        str = (char*)malloc(len_of_str*sizeof(char));

        ++count_strs;

    }

    free(str);



    int num_of_correct_strs = 0;

    char** out = StrFilt(strs, num_of_strs, &num_of_correct_strs);

    for (int i = 0; i < num_of_correct_strs; i++) {

        printf("%s\n", out[i]);

    }

    for (int i = 0; i < num_of_strs; i++) {

        free(strs[i]);

    }

    free(strs);

    free(out);

}