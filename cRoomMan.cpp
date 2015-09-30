#include "cRoomMan.h"

cRoomMan::cRoomMan()
{
	items.clear();
	score = 0;
	score_lab = NULL;
	timer = NULL;
	maxTime = "";
	max_min = 0;
	max_sec = 0;
	m_title = "";
	m_game_end = false;
}

cRoomMan::cRoomMan(const string title, const char *fn)
{
	items.clear();
	timer = NULL;
	maxTime = "";
	max_min = 0;
	max_sec = 0;
	m_title = title;
	LoadRoom(fn);

	int pos_col[5];
	pos_col[0] = 30;
	pos_col[1] = WinHeight - 30;
	pos_col[2] = 0;
	pos_col[3] = 255;
	pos_col[4] = 0;

	score_lab = new cLabel(FONT, pos_col);
	score = 0;
	m_game_end = false;
}

cRoomMan::~cRoomMan()
{
	if (score_lab != NULL) {
		delete score_lab;
		score_lab = NULL;
	}
	if (timer != NULL) {
		delete timer;
		timer = NULL;
	}
	vector<cTexture>::iterator iter = items.begin();
	while (iter != items.end()) {
		 iter->cleanTexMemory(); 
		iter++;
	}
	items.clear();
	score = 0;
	maxTime = "";
	max_min = 0;
	max_sec = 0;
	m_title = "";
	m_game_end = false;
}

void cRoomMan::Draw(const bool named)
{
	vector<cTexture>::iterator iter = items.begin();
	while (iter != items.end()) {
		if (iter->getLive()) {
			glPushMatrix();
			if (iter->getId() > 1) {
				if (iter->getRemoved()) {
					if (iter->getXslide() > 5) {
						iter->setLive(false);
						iter->setRemoved(true);
					}	
				glTranslatef(iter->getXslide(), 0.0, 0.0);
				iter->setXslide(iter->getXslide() + iter->getXinc());
				}
			}
			iter->drawQuad(named); 
			glPopMatrix();
		}
		iter++;
	}

	if (!named && score_lab != NULL) {
		char tex[10];
		_itoa_s(score, tex, size_t(10), 10);
		char scor[20] = "Score: ";
		strcat_s(scor, tex);
		score_lab->OutputLabel(scor);
	}

	if (!named && timer != NULL) 
		timer->showTime();
}

int cRoomMan::processTime()
{
	if (timer != NULL) {
		if (timer->processTime() == 0) return 2;//время вышло
	}

	int i = 0;
	vector<cTexture>::iterator iter = items.begin();
	while (iter != items.end()) {
		if (iter->getRemoved()) i++;
		iter++;
	}
	if (i+1 == items.size() && timer->getWork()) 
		return 1;
		
	return 0;
}

void cRoomMan::LoadRoom(const char *fn)
{
	const string textItem = "item";
	const string textTime = "time";
	string elementName;

	int timer_pos_col[5];
	timer_pos_col[0] = timer_xpos;
	timer_pos_col[1] = timer_ypos;
	timer_pos_col[2] = 255;
	timer_pos_col[3] = 255;
	timer_pos_col[4] = 0;

	TiXmlDocument doc(fn);
	doc.LoadFile();
	TiXmlElement* root = doc.FirstChildElement("room");
	TiXmlElement* element = root->FirstChildElement();

	cTexture item;

	while (element != NULL)
	{
		elementName = element->Value();
		if (elementName == textTime) {//loading clock
			TiXmlAttribute* attr = element->FirstAttribute();//first attribute
			string val1 = attr->Value();
			int min = atoi(val1.c_str());
			attr = attr->Next();//second attribute
			string val2 = attr->Value();
			int sec = atoi(val2.c_str());
			timer = new cTimer(min, sec, timer_pos_col);
			setMaxTime(val1, val2, min, sec);
		} else
		if (elementName == textItem) {//loading object
			TiXmlAttribute* attr = element->FirstAttribute();//first attribute
			string val = attr->Value();
			int id = atoi(val.c_str());
			attr = attr->Next();//second attribute
			string name = attr->Value();
			attr = attr->Next();
			int xoff = atoi(string(attr->Value()).c_str());
			attr = attr->Next();
			int yoff = atoi(string(attr->Value()).c_str());
			attr = attr->Next();
			int width = atoi(string(attr->Value()).c_str());
			attr = attr->Next();
			int height = atoi(string(attr->Value()).c_str());
			attr = attr->Next();
			float xy[8];
			for (int i = 0; i < 8; i++) {
				xy[i] = atof(string(attr->Value()).c_str());
				attr = attr->Next();
			}
			string fileName = attr->Value();
			item = cTexture(id, name, xy, xoff, yoff, width, height, fileName.c_str());
			items.push_back(item);
		}
		element = element->NextSiblingElement();
	}//while
}

void cRoomMan::setMaxTime(string val1, string val2, const int min, const int sec)
{
	if (val1.length() == 1)
		val1.insert(0, "0");
	if (val2.length() == 1)
		val2.insert(0, "0");
	maxTime = val1 + ":" + val2;
	max_min = min;
	max_sec = sec;
}

void cRoomMan::pickItem(const int hit)
{
	vector<cTexture>::iterator iter = items.begin();
	while (iter != items.end()) {
		if (iter->getId() == hit && !iter->getRemoved()) {
			iter->setRemoved(true);
			addScore(10);
		}
		iter++;
	}
}

void cRoomMan::addScore(const int num)
{
	score += num;
}

void cRoomMan::subScore(const int num)
{
	score -= num;
}

void cRoomMan::setTimer(const bool work)
{ 
	if (timer != NULL) timer->setWork(work); 
}

bool cRoomMan::getTimer()
{
	bool b = false;
	if (timer != NULL) 
		b = timer->getWork();
	return b;
}