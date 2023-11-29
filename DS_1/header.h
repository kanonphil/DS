#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <crtdbg.h>

typedef int element;

typedef struct node
{
	element data;
	struct node* next;
} NODE;
