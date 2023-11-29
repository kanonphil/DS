#pragma once

#include <time.h>

// ���� �ð��� �� �ð��� ���� ����ü�Դϴ�.
typedef struct tick_time
{
	clock_t s_tick;
	clock_t e_tick;
} Tick;

// Ÿ�̸Ӹ� �����մϴ�.
void start(Tick* tick)
{
	tick->s_tick = clock();
}

// Ÿ�̸Ӹ� �����մϴ�.
void end(Tick* tick)
{
	tick->e_tick = clock();
}

// Ÿ�̸��� ����� �ð��� ������� �� �ð����� ���մϴ�.
clock_t get_term(Tick* tick)
{
	return tick->e_tick - tick->s_tick;
}