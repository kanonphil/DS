#pragma once

#include <stdlib.h>
#include "Structure.h"

Array* create_array(size_t count)
{
	Array* result = (Array*)malloc(sizeof(Array));

	result->address = (element*)malloc(sizeof(element) * count);
	result->count = count;

	return result;
}

void write_array(Array* array, size_t index, element data)
{
	if (index >= 0 && index < array->count)
	{
		array->address[index] = data;
	}
}

Bool find_array(Array* array, element data)
{
	for (int i = 0; i < array->count; i++)
	{
		if (array->address[i] == data)
		{
			return TRUE;
		}
	}

	return FALSE;
}