#pragma once

#include <time.h>

// 시작 시간과 끝 시간을 지닌 구조체입니다.
typedef struct tick_time
{
	clock_t s_tick;
	clock_t e_tick;
} Tick;

// 타이머를 시작합니다.
void start(Tick* tick)
{
	tick->s_tick = clock();
}

// 타이머를 종료합니다.
void end(Tick* tick)
{
	tick->e_tick = clock();
}

// 타이머의 저장된 시간을 기반으로 한 시간차를 구합니다.
clock_t get_term(Tick* tick)
{
	return tick->e_tick - tick->s_tick;
}