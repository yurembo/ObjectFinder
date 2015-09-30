#include <vector>
#include <string>
#include "cTexture.h"
#include "cLabel.h"

using namespace std;

struct sTime
{
	int min;
	int sec;
};

class cDlgMan
{
private:
	vector<cTexture>textures;
	vector<cLabel>labels;
	string m_title;
	vector<string>strings;
	string m_record;

	void createPauseDlg(const string maxTime, const string bestTime);
	void createWinDlg(const int m, const int s, const string maxTime, const string bestTime);
	void createButtons();
	void createBackground(const string fileName);
	void createLossDlg();
	void createFewEnergyDlg(const int yourEnergy, const int roomEnergy);
	sTime getTime(const string bestTime);
	bool compareTimes(sTime time1, sTime time2);
	string AddZeroToTime(const string str);

public:
	cDlgMan();
	cDlgMan(const string title, const string maxTime, const string bestTime);
	cDlgMan(const string title, const int m, const int s);
	cDlgMan(const string title, const int yourTime, const int roomTime, const string maxTime, const string bestTime);
	cDlgMan(const string title);
	~cDlgMan();
	void Draw(const bool named);
	void DrawLabel();
	string getTitle() { return m_title; }
	string subtractionTimes(const string maxTime, const string bestTime);
	string sTimeToStr(const sTime time);
	string getRecord() { return m_record; }
	void setRecord(const string record) { m_record = record; }
};