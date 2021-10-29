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
   ��������� ������ � ������
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
   ������� �������� ������
*/

void CompressFile(FILE* input, BFILE* output);
void DecompressFile(BFILE* input, FILE* output);
void usage_exit(char* prog_name);

/*---------------------------------------------------------
   ������� ������ � ������� ������ ��� ��������� LZW
*/

unsigned int find_dictionary_match(int prefix_code, int character);
unsigned int decode_string(unsigned int offset, unsigned int code);

/*---------------------------------------------------------
   ���������, ������������ ��� ������ LZW
*/
/* ���������� ����� � ���� */
#define BITS                       12
/* ������������ �������� ���� */
#define MAX_CODE                   ( ( 1 << BITS ) - 1 )
/* ������ ������� � ��������� */
#define TABLE_SIZE                 5021
/* ����������� ��� ����� ������ */
#define END_OF_STREAM              256
/* �������� ����, ������� �������� ������ �����������
� ������� ����� */
#define FIRST_CODE                 257
/* ������� ��������� ������ � ������� */
#define UNUSED                     -1

// ��� �����-�����������
const char* compressor_filname = "LZW.exe";

/* ��������� ������� ��� ��������� LZW */

struct dictionary
{
	int code_value;
	int prefix_code;
	char character;
}
dict[TABLE_SIZE];

/* ���� ��� ������������� */

char decode_stack[TABLE_SIZE];

