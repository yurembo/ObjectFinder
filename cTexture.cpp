#include "ctexture.h"

cTexture::cTexture()
{
	m_id = 0;
	m_objName = "";
	m_quadDisplayListId = 0;
	m_pixmap = NULL;
	m_gl_texture_id =- 1;
	m_tex_Xoffset = 0;
	m_tex_Yoffset = 0;
	m_tex_width = 0;
	m_tex_height = 0;
	live = true;
	removed = false;
	m_Xslide = 0.0;
	m_Xinc = 0.0;
	m_Xtarget = 0.0;
	m_placeHolder = 0;
}

cTexture::cTexture(const int id, const string name, const float *xy, const float xoff, const float yoff,
				   const float width, const float height,const char *filename)
{
	m_id = id;
	m_objName = name;
	buildQuad(xy);

	m_tex_Xoffset = xoff;
	m_tex_Yoffset = yoff;
	m_tex_width = width;
	m_tex_height = height;

	m_quadDisplayListId = 0;
	m_pixmap = NULL;
	m_gl_texture_id =- 1;
	live = true;
	removed = false;
	m_Xslide = 0.0;
	m_Xinc = TEX_MOV_SPEED;
	m_Xtarget = 0.0;
	m_placeHolder = id;

	TextureLoader(width, height, filename);
	setQuadTexture();
}

cTexture::cTexture(const cTexture& tex)
{
	m_id = tex.m_id;
	m_objName = tex.m_objName;
	m_gl_texture_id = tex.m_gl_texture_id;
	m_pixmap = tex.m_pixmap;
	m_tex_Xoffset = tex.m_tex_Xoffset;
	m_tex_Yoffset = tex.m_tex_Yoffset;
	m_tex_width = tex.m_tex_width;
	m_tex_height = tex.m_tex_height;
	live = tex.live;
	removed = tex.removed;
	m_Xslide = tex.m_Xslide;
	m_Xinc = tex.m_Xinc;
	m_Xtarget = tex.m_Xtarget;
	m_placeHolder = tex.m_placeHolder;
	for (int i = 0; i < 4; i++) m_arrQuadVertices[i] = tex.m_arrQuadVertices[i];
	m_quadDisplayListId = tex.m_quadDisplayListId;
}

cTexture& cTexture::operator=(const cTexture& tex)
{
	if (this == &tex) return *this;

	if (&tex != NULL) {
		m_id = tex.m_id;
		m_objName = tex.m_objName;
		m_gl_texture_id = tex.m_gl_texture_id;
		m_pixmap = tex.m_pixmap;
		m_tex_Xoffset = tex.m_tex_Xoffset;
		m_tex_Yoffset = tex.m_tex_Yoffset;
		m_tex_width = tex.m_tex_width;
		m_tex_height = tex.m_tex_height;
		live = tex.live;
		removed = tex.removed;
		m_Xslide = tex.m_Xslide;
		m_Xinc = tex.m_Xinc;
		m_Xtarget = tex.m_Xtarget;
		m_placeHolder = tex.m_placeHolder;
		for (int i = 0; i < 4; i++) m_arrQuadVertices[i] = tex.m_arrQuadVertices[i];
		m_quadDisplayListId = tex.m_quadDisplayListId;
	}

	return *this;
}

cTexture::~cTexture()
{
	if (m_pixmap)
	{
//		delete[] m_pixmap;
		m_pixmap = NULL;
	}
	if (m_gl_texture_id != NULL) ilDeleteImage(m_gl_texture_id);
	m_placeHolder = 0;
	m_Xslide = 0.0;
	m_Xtarget = 0.0;
	m_Xinc = 0.0;
	live = false;
	removed = false;
	m_quadDisplayListId = 0;
	m_gl_texture_id =- 1;
	m_tex_Xoffset = 0;
	m_tex_Yoffset = 0;
	m_tex_width = 0;
	m_tex_height = 0;
	m_objName = "";
	m_id = 0;
}

bool cTexture::TextureLoader(const int width, const int height,const char* filename)
{
	ILuint ImgId = 0;
	ilGenImages(1, &ImgId);

	ilBindImage(ImgId);

	if (!filename)
		return false;

	if (!ilLoadImage(filename))
	{
		return false;
	}

	setTexWidth(width);
	setTexHeight(height);

	int bytesPerPixel = ilGetInteger(IL_IMAGE_BPP);
	if (bytesPerPixel != 3)
	{
		return false;
	}
	
	setPixmap(getTexWidth() * getTexHeight());
	if (!getPixmap())
	{
		return false;
	}

	ilCopyPixels(getTexXoffset(), getTexYoffset(), 0, getTexWidth(), getTexHeight(), 1, IL_RGBA, IL_UNSIGNED_BYTE, getPixmap());

	if (m_id > 1) setColorKey(20, 20, 20);//если не фон, тогда применяем цветовой ключ
	
	ilBindImage(0);
    ilDeleteImage(ImgId);

  return true;
}

bool cTexture::buildQuad(const float *xy)
{
	m_arrQuadVertices[0].m_position.x = xy[0];
	m_arrQuadVertices[0].m_position.y = xy[1];
	m_arrQuadVertices[0].m_position.z = 0.0f;
	m_arrQuadVertices[0].m_uv.u = 0.0f;
	m_arrQuadVertices[0].m_uv.v = 0.0f;

	m_arrQuadVertices[1].m_position.x = xy[2];
	m_arrQuadVertices[1].m_position.y = xy[3];
	m_arrQuadVertices[1].m_position.z = 0.0f;
	m_arrQuadVertices[1].m_uv.u = 1.0f;
	m_arrQuadVertices[1].m_uv.v = 0.0f;


	m_arrQuadVertices[2].m_position.x = xy[4];
	m_arrQuadVertices[2].m_position.y = xy[5];
	m_arrQuadVertices[2].m_position.z = 0.0f;
	m_arrQuadVertices[2].m_uv.u = 1.0f;
	m_arrQuadVertices[2].m_uv.v = 1.0f;

	m_arrQuadVertices[3].m_position.x = xy[6];
	m_arrQuadVertices[3].m_position.y = xy[7];
	m_arrQuadVertices[3].m_position.z = 0.0f;
	m_arrQuadVertices[3].m_uv.u = 0.0f;
	m_arrQuadVertices[3].m_uv.v = 1.0f;

	return true;
}

void cTexture::setQuadTexture()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &m_gl_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_gl_texture_id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getTexWidth(), getTexHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, getPixmap());
}

void cTexture::drawQuad(const bool named)
{
	if (named) glDisable(GL_TEXTURE_2D);

	glColor4f(1.0f, 1.0f, 1.0f, 0.5); 

	glPushMatrix();
	if (getId() == 1) glTranslatef(0.0, 0.0, -0.01);

	if (!named) 
	glBindTexture(GL_TEXTURE_2D, m_gl_texture_id);

	if (named) glLoadName(m_id);

	glBegin(GL_TRIANGLES);
	{
		// Front Face. 
		glNormal3f( 0.0f, 0.0f, 1.0f);
		
		// Face 0.
		glTexCoord2fv(m_arrQuadVertices[0].m_uv.texCoord); 
		glVertex4fv(m_arrQuadVertices[0].m_position.v);
		glTexCoord2fv(m_arrQuadVertices[1].m_uv.texCoord);
		glVertex4fv(m_arrQuadVertices[1].m_position.v);
		glTexCoord2fv(m_arrQuadVertices[2].m_uv.texCoord); 
		glVertex4fv(m_arrQuadVertices[2].m_position.v);

		// Face 1.
		//glTexCoord2fv(m_arrQuadVertices[2].m_uv.texCoord); 
		glVertex4fv(m_arrQuadVertices[2].m_position.v);
		glTexCoord2fv(m_arrQuadVertices[3].m_uv.texCoord); 
		glVertex4fv(m_arrQuadVertices[3].m_position.v);
		glTexCoord2fv(m_arrQuadVertices[0].m_uv.texCoord); 
		glVertex4fv(m_arrQuadVertices[0].m_position.v);
	}
	glEnd();
	glPopMatrix();
}

void cTexture::setColorKey(const int r, const int g, const int b)
{
		cRGBA_Byte_Pixel *pix = getPixmap();

		int imageSize  = getTexWidth() * getTexHeight();

        for(int i = 0; i < imageSize; i++)
        {
			if (pix->r <= r && pix->g <= g && pix->b <= b)
                pix->a = 0;
            else
                pix->a = 255; 

			pix++;
		}
}

void cTexture::cleanTexMemory()
{
	if (m_pixmap)
	{
		delete[] m_pixmap;
	}
}