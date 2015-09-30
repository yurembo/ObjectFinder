//здесь находятся элементарные типы данных, служащие для построения более сложных объектов

#pragma once

typedef unsigned char u8;

class cRGBA_Byte_Pixel
{
public:
	cRGBA_Byte_Pixel()
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	};

	union
	{
		struct
		{
			u8 r;
			u8 g;
			u8 b;
			u8 a;
		};
		u8 rgb[4];
	};
}; 

class cVector4f
{
public:
  cVector4f() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) { }

	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w; 
		};
		struct
		{
			float r;
			float g;
			float b;
			float a; 
		};
		float v[4];
	};
};

class cTextCoord
{
public:
  cTextCoord() : u(0.0f), v(0.0f)  { }
    
	union
	{
		struct
		{
			float u;
			float v;
		};
		float texCoord[2];
	};
};

class cVertex
{
public:
	cVertex() {}
	cVector4f m_position;
	cVector4f m_normal;
	cVector4f m_color;
	cTextCoord m_uv;
};