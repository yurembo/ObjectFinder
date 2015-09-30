#include "cLabel.h"

cLabel::cLabel()
{
	font = NULL;
	x = 0;
	y = 0;
	r = 0;
	g = 0;
	b = 0;
}

cLabel::cLabel(void *f, const int *pos_col)
{
	font = f;
	x = pos_col[0];
	y = pos_col[1];
	r = pos_col[2];
	g = pos_col[3];
	b = pos_col[4];
}

cLabel::cLabel(const cLabel& lab)
{
	x = lab.x;
	y = lab.y;
	r = lab.r;
	g = lab.g;
	b = lab.b;
	font = lab.font;
}

cLabel& cLabel::operator =(const cLabel &lab)
{
	if (this == &lab) return *this;

	if (&lab != NULL) {
		x = lab.x;
		y = lab.y;
		r = lab.r;
		g = lab.g;
		b = lab.b;
		font = lab.font;
	}
	return *this;
}

cLabel::~cLabel()
{
	font = NULL;
	x = 0;
	y = 0;
	r = 0;
	g = 0;
	b = 0;
}

void cLabel::OutputLabel(char *str)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);//отключаем текстуру, чтобы включить цвет
	glMatrixMode(GL_PROJECTION);//установка матрицы проекции для вывода текста
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WinWidth, 0, WinHeight);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(r, g, b);		
	//Установка позиции для вывода подписи
	glRasterPos2f(x, y);	
	//Вывод подписи
	PrintLabel(str);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void cLabel::PrintLabel(char *tex)
{
	char *c = tex;
	while (*c)
	{
		glutBitmapCharacter(font, *c);
		c++;
	}
}