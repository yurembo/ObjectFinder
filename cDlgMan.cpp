#include "cDlgMan.h"

cDlgMan::cDlgMan()
{
	textures.clear();
	labels.clear();
	m_title.clear();
	strings.clear();
	m_record.clear();
}

cDlgMan::~cDlgMan()
{
	vector<cTexture>::iterator iter = textures.begin();
	while (iter != textures.end()) {
		 iter->cleanTexMemory(); 
		iter++;
	}
	textures.clear();
	labels.clear();
	m_title.clear();
	strings.clear();
	m_record.clear();
}

cDlgMan::cDlgMan(const string title, const string maxTime, const string bestTime)
{
	m_title = title;
	textures.clear();
	labels.clear();
	strings.clear();
	m_record.clear();

	if (m_title == PAUSE) 
		createPauseDlg(maxTime, bestTime);
}

cDlgMan::cDlgMan(const string title, const int m, const int s)
{
	m_title = title;
	textures.clear();
	labels.clear();
	strings.clear();

	createFewEnergyDlg(m, s);
}

cDlgMan::cDlgMan(const string title, const int m, const int s, const string maxTime, const string bestTime)
{
	m_title = title;
	textures.clear();
	labels.clear();
	strings.clear();

	createWinDlg(m, s, maxTime, bestTime);
}

cDlgMan::cDlgMan(const string title)
{
	m_title = title;
	textures.clear();
	labels.clear();
	strings.clear();

	createLossDlg();
}

void cDlgMan::createBackground(const string fileName)
{
	float xy[8];
	xy[0] = -0.5;
	xy[1] = -0.5;
	xy[2] = 0.5;
	xy[3] = -0.5;
	xy[4] = 0.5;
	xy[5] = 0.5;
	xy[6] = -0.5;
	xy[7] = 0.5;

	cTexture tex = cTexture(1, m_title, xy, 0, 0, 640, 640, fileName.c_str());
	textures.push_back(tex);
}

void cDlgMan::createButtons()
{
	float xy1[8] = { -0.4, -0.4, -0.25, -0.4, -0.25, -0.25, -0.4, -0.25 };
	cTexture tex = cTexture(2, "Yes", xy1, 0, 0, 100, 100, "Dlgs\\Yes.png");
	textures.push_back(tex);

	float xy2[8] = { 0.25, -0.4, 0.4, -0.4, 0.4, -0.25, 0.25, -0.25 };
	tex = cTexture(3, "No", xy2, 0, 0, 100, 100, "Dlgs\\No.png");
	textures.push_back(tex);  
}

void cDlgMan::createPauseDlg(const string maxTime, const string bestTime)
{
	createBackground("Dlgs\\pause.png");

	createButtons();

	if (maxTime != "") {
		int pos_col[5] = { WinWidth / 2 + 100, WinHeight / 2 + 50, 0, 0, 255 };
		cLabel lab = cLabel(FONT, pos_col);
		labels.push_back(lab);

		string str = maxTime;
		strings.push_back(AddZeroToTime(str));
	}

	if (bestTime != "") {
		int pos_col1[5] = { WinWidth / 2 + 100, WinHeight / 2 + 20, 0, 0, 255 };
		cLabel lab = cLabel(FONT, pos_col1);
		labels.push_back(lab);

		string str = bestTime;//subtractionTimes(maxTime, bestTime);
		strings.push_back(AddZeroToTime(str));

		m_record = str;
	}
}

void cDlgMan::createWinDlg(const int m, const int s, const string maxTime, const string bestTime)
{
	sTime s_myTime = { m, s };
	string str_myTime = sTimeToStr(s_myTime);
	str_myTime = subtractionTimes(maxTime, str_myTime);
	sTime s_bestTime = getTime(bestTime);
	s_myTime = getTime(str_myTime);
	bool res = compareTimes(s_myTime, s_bestTime);

	if (!res) createBackground("Dlgs\\win.png"); 
	else createBackground("Dlgs\\win_rec.png"); 
	createButtons();

	strings.push_back(AddZeroToTime(str_myTime));

	int pos_col[5] = { WinWidth / 2 + 100, WinHeight / 2 + 50, 0, 0, 255 };
	cLabel label = cLabel(FONT, pos_col);
	labels.push_back(label);

	if (bestTime != "")
	{
		strings.push_back(AddZeroToTime(bestTime));

		int pos_col1[5] = { WinWidth / 2 + 100, WinHeight / 2 + 20, 0, 0, 255 };
		label = cLabel(FONT, pos_col1);
		labels.push_back(label);

		if (compareTimes(getTime(str_myTime), getTime(bestTime)))
			m_record = AddZeroToTime(str_myTime);
		else
			m_record = AddZeroToTime(bestTime);
	}
}

void cDlgMan::createLossDlg()
{
	createBackground("Dlgs\\loss.png");
	createButtons();
}

void cDlgMan::createFewEnergyDlg(const int yourEnergy, const int roomEnergy)
{
	createBackground("Dlgs\\few.png");

	float xy1[8] = { -0.1, -0.4, 0.1, -0.4, 0.1, -0.25, -0.1, -0.25 };
	cTexture tex = cTexture(2, "OK", xy1, 0, 0, 100, 100, "Dlgs\\OK.png");
	textures.push_back(tex);

	int pos_col[5] = { WinWidth / 2 + 100, WinHeight / 2 + 30, 0, 0, 255 };
	cLabel label = cLabel(FONT, pos_col);
	labels.push_back(label);

	int pos_col1[5] = { WinWidth / 2 + 100, WinHeight / 2 - 2, 0, 0, 255 };
	label = cLabel(FONT, pos_col1);
	labels.push_back(label);

	char ye[10];
	_itoa_s(yourEnergy, ye, size_t(10), 10);
	string str = string(ye);
	strings.push_back(str);

	char re[10];
	_itoa_s(roomEnergy, re, size_t(10), 10);
	str = string(re);
	strings.push_back(str);
}

void cDlgMan::Draw(const bool named)
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.02);

	vector<cTexture>::iterator iter = textures.begin();
	while (iter != textures.end()) {
			iter->drawQuad(named); 
		iter++;
	}

	glPopMatrix();
}

void cDlgMan::DrawLabel()
{
	unsigned int i = 0;
	vector<cLabel>::iterator ter = labels.begin();
	while (ter != labels.end() && i <= strings.size()) {
			char str[50]; 
			memset(str, 0, sizeof(str));
			strncpy_s(str, 50, strings.at(i).c_str(), sizeof(str) - 1);
			ter->OutputLabel(str);
		i++;
		ter++;
	}
}

//функции для работы с выводом времени (короткий формат)
sTime cDlgMan::getTime(const string bestTime)
{
	string bTime = bestTime;
	string p1 = "", p2 = "";
	int sym = -1;
	for (unsigned int i = 0; i < bTime.length(); i++) {
		char ch = bTime[i];
		if (strncmp(&ch, ":", 1) != 0 && sym == -1) 
			p1 = p1 + ch; else
		if (strncmp(&ch, ":", 1) != 0 && sym > -1) 
			p2 = p2 + ch; else
		if (strncmp(&ch, ":", 1) == 0) 
			sym = i;
	}
	sTime time = { 0, 0 };
	time.min = atoi(p1.c_str());
	time.sec = atoi(p2.c_str());

	return time;
}

bool cDlgMan::compareTimes(sTime time1, sTime time2)
{
	bool res = false;

	if (time1.min > time2.min) res = false;
	else
		if (time1.min < time2.min) res = true;
		else
			if (time1.min == time2.min) {
				if (time1.sec >= time2.sec) res = false;
				else
					if (time1.sec < time2.sec) res = true;
			}

	return res;//Time1 > Time2 : false; Time1 < Time2 : true
}

string cDlgMan::sTimeToStr(const sTime time)
{
	int min = time.min;
	int sec = time.sec;
	char chM[10];
	memset(chM, 0, sizeof(chM));
	_itoa_s(min, chM, 10, 10);
	string str1 = string(chM);
	char chS[10];
	_itoa_s(sec, chS, 10, 10);
	string str2 = string(chS);
	string res = str1 + ":" + str2;
	return res;
}

string cDlgMan::subtractionTimes(const string maxTime, const string bestTime)
{
	string res = "";
	sTime time1 = getTime(maxTime);
	sTime time2 = getTime(bestTime);
	sTime resTime = { 0, 0 };
	resTime.sec = time1.sec - time2.sec;
	resTime.min = time1.min - time2.min;
	if (resTime.sec < 0) {
		resTime.sec = g_max_sec + resTime.sec;
		resTime.min = resTime.min - 1;
	}
	if (resTime.min < 0) resTime.min = 0;

	res = sTimeToStr(resTime);

	return res;
}

string cDlgMan::AddZeroToTime(const string str)
{
	string rec = str;
	string p1 = "", p2 = "";
	int sym = -1;
	for (unsigned int i = 0; i < rec.length(); i++) {
		char ch = rec[i];
		if (strncmp(&ch, ":", 1) != 0 && sym == -1) 
			p1 = p1 + ch; else
		if (strncmp(&ch, ":", 1) != 0 && sym > -1) 
			p2 = p2 + ch; else
		if (strncmp(&ch, ":", 1) == 0) 
			sym = i;
	}

	if (p1.length() == 1)
		p1.insert(0, "0");
	if (p2.length() == 1)
		p2.insert(0, "0");

	rec = p1 + ":" + p2;
	
	return rec;
}