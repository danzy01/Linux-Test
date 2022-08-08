#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#define buf_size 256
#define stat_fields 11
pthread_mutex_t mutex;
size_t a=2;
size_t b=3;
size_t core_amount=1;
size_t** tab = NULL;
size_t** ptab = NULL;
double* p_core_usage=NULL;

size_t initialize();
void free_global(void);
void *thread_func(void *arg);
void *zapis(void *arg);
void size_check(void);
void *read_th(void *arg);
void *analyze_th(void *arg);
void *print_th(void *arg);
