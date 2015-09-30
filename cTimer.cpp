#include "cTimer.h"

cTimer::cTimer()
{
	m_min = m_sec = 0;
	label = NULL;
	m_work = true;
}

cTimer::cTimer(const int m, const int s, const int *pos_col)
{
	m_min = m;
	m_sec = s;
	label = new cLabel(FONT, pos_col);
	m_work = true;
}

cTimer::~cTimer()
{
	m_min = 0;
	m_sec = 0;
	if (label != NULL) {
		delete label;
		label = NULL;
	}
	m_work = true;
}

void cTimer::showTime()
{
	char time[30] = "Time: ";
	char min[10];
	char sec[10];
	_itoa_s(m_min, min, size_t(10), 10);
	_itoa_s(m_sec, sec, size_t(10), 10);
	strcat_s(time, min);
	strcat_s(time, ":");
	strcat_s(time, sec);
	label->OutputLabel(time);
}

int cTimer::processTime()
{
	if (!m_work) return 1;

	if (m_min == 0 && m_sec == 0)
	return 0;

	if (m_sec > 0)
		m_sec--; else
		if (m_min > 0) {
			m_min--;
			m_sec = g_max_sec;
		}
	return 1;
}