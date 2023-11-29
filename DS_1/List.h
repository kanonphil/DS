#pragma once
#include "header.h"

typedef struct list
{
	NODE* begin;
	NODE* end;
	size_t size;
} LIST;

void l_construct(LIST**);
void l_destruct(LIST**);

bool l_empty(LIST*);
size_t l_size(LIST*);
element* l_at(LIST*, size_t);

void l_insert(LIST*, size_t, element);
void l_erase(LIST*, size_t);
void l_clear(LIST*);

void l_append(LIST*, LIST**);
void l_split(LIST*, LIST**, size_t);

size_t l_find_element(LIST*, element);
void l_reverse(LIST*);
void l_sort(LIST*, bool);
