#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ctype.h>

//typedef unsigned char unsigned char;
//typedef unsigned long unsigned long;
//typedef unsigned int  unsigned int;

/*---------------------------------------------------------
   Побитовый доступ к файлам
*/

typedef struct bfile
{
    FILE* file;
    unsigned char mask;
    int rack;
    int pacifier_counter;
}
BFILE;

#define PACIFIER_COUNT 2047

BFILE* OpenInputBFile(char* name);
BFILE* OpenOutputBFile(char* name);
void  WriteBit(BFILE* bfile, int bit);
void  WriteBits(BFILE* bfile, unsigned long code, int count);
int   ReadBit(BFILE* bfile);
unsigned long ReadBits(BFILE* bfile, int bit_count);
void  CloseInputBFile(BFILE* bfile);
void  CloseOutputBFile(BFILE* bfile);

/*---------------------------------------------------------
   Функции высокого уровня
*/

void CompressFile(FILE* input, BFILE* output);
void DecompressFile(BFILE* input, FILE* output);
void usage_exit(char* prog_name);

/*---------------------------------------------------------
   Функции работы с моделью данных для алгоритма LZW
*/

unsigned int find_dictionary_match(int prefix_code, int character);
unsigned int decode_string(unsigned int offset, unsigned int code);

/*---------------------------------------------------------
   Константы, используемые при работе LZW
*/
/* Количество битов в коде */
#define BITS                       12
/* Максимальное значение кода */
#define MAX_CODE                   ( ( 1 << BITS ) - 1 )
/* Размер словаря в элементах */
#define TABLE_SIZE                 5021
/* Специальный код конца потока */
#define END_OF_STREAM              256
/* Значение кода, которое получает первая добавленная
в словарь фраза */
#define FIRST_CODE                 257
/* Признак свободной ячейки в словаре */
#define UNUSED                     -1

// имя файла-компрессора
const char* compressor_filname = "LZW.exe";

/* Структура словаря для алгоритма LZW */

struct dictionary
{
	int code_value;
	int prefix_code;
	char character;
}
dict[TABLE_SIZE];

/* Стек для декодирования */

char decode_stack[TABLE_SIZE];

