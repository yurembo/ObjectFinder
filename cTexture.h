#pragma once

#include <string>
#include "init.h"
#include "Elements.h"

#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#pragma comment(lib, "devil.lib")
#pragma comment(lib, "ilu.lib")
#pragma comment(lib, "ilut.lib")

using namespace std;

class cTexture
{
private:
	int m_id;
	string m_objName;
	unsigned int m_gl_texture_id;
	cRGBA_Byte_Pixel *m_pixmap;
	int m_tex_Xoffset;
	int m_tex_Yoffset;
	int m_tex_width;
	int m_tex_height;
	cVertex m_arrQuadVertices[4];
	unsigned long m_quadDisplayListId;
	bool live;
	bool removed;
	float m_Xslide;//улетание объекта
	float m_Xinc;
	float m_Xtarget;
	int m_placeHolder;

	bool buildQuad(const float *xy);
	void setQuadTexture();
	bool TextureLoader(const int width, const int height, const char* filename);

public:
	cTexture();
	cTexture(const int id, const string name, const float *xy, const float xoff, const float yoff, const float width, const float height,const char *filename);
	cTexture(const cTexture& tex);//конструктор копирования
	cTexture& operator=(const cTexture& tex);//перегруженный оператор присваивания
	~cTexture();

	void setID(const int id) { m_id = id; }
	int getId() { return m_id; }
	void setName(const string name) { m_objName = name; }
	string getName() { return m_objName; }
	cRGBA_Byte_Pixel *getPixmap() { return m_pixmap; }
	void setPixmap(const int pix) { m_pixmap = new cRGBA_Byte_Pixel[pix]; }
	void setTexXoffset(const int offset) { m_tex_Xoffset = offset; }
	int getTexXoffset() { return m_tex_Xoffset; }
	void setTexYoffset(const int offset) { m_tex_Yoffset = offset; }
	int getTexYoffset() { return m_tex_Yoffset; }
	void setTexWidth(const int width) { m_tex_width = width; }
	int getTexWidth() { return m_tex_width; }
	void setTexHeight(const int height) { m_tex_height = height; }
	int getTexHeight() { return m_tex_height; }
	void setLive(const bool l) { live = l; }
	bool getLive() { return live; }
	void setRemoved(const bool rem) { removed = rem; }
	bool getRemoved() { return removed; }
	void setXslide(const float slide ) { m_Xslide = slide; }
	float getXslide() { return m_Xslide; }
	void setXinc(const float inc) { m_Xinc = inc; }
	float getXinc() { return m_Xinc; }
	void setXtarget(const float tar) { m_Xtarget = tar; }
	float getXtarget() { return m_Xtarget; }
	void setPlaceHolder(const int place) { m_placeHolder = place; }
	int getPlaceHolder() { return m_placeHolder; }
	void drawQuad(const bool named);
	void setColorKey(const int r, const int g, const int b);
	void cleanTexMemory();
};

