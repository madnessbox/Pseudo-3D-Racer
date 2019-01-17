#pragma once
#include <Windows.h>
#include <cstdlib>
#include <cstdInt>
#include <WinBase.h>
#include <math.h>
#include <time.h>

static uint64 _timer_frequency;
static fp64 _timer_us_factor;
static fp64 _timer_ms_factor;


typedef uint64 timer_t;

enum {
	TIMER_MS_PER_S = 1000,
	TIMER_US_PER_MS = 1000,
	TIMER_US_PER_S = TIMER_MS_PER_S * TIMER_US_PER_MS,
};

void timer_init()
{
	LARGE_INTEGER timer_freq;
	QueryPerformanceFrequency(&timer_freq);
	_timer_frequency = (timer_freq.QuadPart);
	_timer_us_factor = (fp64)TIMER_US_PER_S / (fp64)_timer_frequency;
	_timer_ms_factor = (fp64)TIMER_MS_PER_S / (fp64)_timer_frequency;
}

timer_t timer_get_counter()
{
	LARGE_INTEGER amount;
	QueryPerformanceCounter(&amount);
	return (uint64)(amount.QuadPart);
}

uint64 timer_get_delta_us(timer_t start, timer_t stop)
{
	fp64 delta = (fp64)(stop - start) * _timer_us_factor;
	return (uint64)delta;
}

timer_t timer_us_to_clocks(uint64 us)
{
	return us * _timer_frequency;
}

uint64 timer_get_delta_ms(timer_t start, timer_t stop)
{
	fp64 delta = (fp64)(stop - start) * _timer_ms_factor;
	return (uint64)delta;
}

uint64 timer_get_delta_s(timer_t start, timer_t stop)
{
	fp64 delta = (fp64)(stop - start) / _timer_frequency;
	return (uint64)delta;
}

uint64 timer_get_absolute_time_us(timer_t time)
{
	return time * (TIMER_US_PER_S / _timer_frequency);
}