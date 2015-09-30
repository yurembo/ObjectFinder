#pragma once

#include "init.h"
#include "cLabel.h"

const int timer_xpos = 200;
const int timer_ypos = WinHeight - 30;

class cTimer
{
private:
	int m_min, m_sec;
	cLabel *label;
	bool m_work;

public:
	cTimer();
	cTimer(const int m, const int s, const int *pos_col);
	~cTimer();

	void showTime();
	int processTime();//2 состояния: 0 - продолжаем работать, 0 - время вышло
	void setWork(const bool b) { m_work = b; }
	bool getWork() { return m_work; }

	int getMin() { return m_min; }
	int getSec() { return m_sec; }
};