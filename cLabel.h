#pragma once;

#include "init.h"

class cLabel
{
private:
	int x, y;
	int r, g, b;
	void* font;

	void PrintLabel(char *tex);
public:
	cLabel();
	cLabel(void *f, const int *pos_col);
	cLabel(const cLabel& lab);//конструктор копирования
	cLabel& operator=(const cLabel& lab);//перегруженный оператор присваивания
	~cLabel();

	void OutputLabel(char *str);
};