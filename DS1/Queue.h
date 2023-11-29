#pragma once
#include "header.h"

typedef struct queue
{
	NODE* begin;
	size_t size;
} QUEUE;

void q_construct(QUEUE**);
void q_destruct(QUEUE**);

bool q_empty(QUEUE*);
size_t q_size(QUEUE*);

void q_push(QUEUE*, element);
element q_pop(QUEUE*);
void q_clear(QUEUE*);