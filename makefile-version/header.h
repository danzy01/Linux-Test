#ifndef HEADER_H
#define HEADER_H
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#define buf_size 256
#define stat_fields 11


size_t initialize();
void free_global(void);
void unit_result_test(void);

void size_check(void);
void *read_th(void*);
void *analyze_th(void*);
void *print_th(void*);

#endif
