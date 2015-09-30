#include <vector>
#include <string>
#include "tinyxml\tinyxml.h"
#include "CTexture.h"
#include "cTimer.h"

//менеджер комнат
class cRoomMan
{
private:	
	int score;
	cLabel *score_lab;
	cTimer *timer;
	string maxTime;
	int max_min, max_sec;
	string m_title;
	bool m_game_end;//флаг конца игры

protected:
	vector<cTexture>items;

	void LoadRoom(const char *fn);

public:
	cRoomMan();
	cRoomMan(const string title, const char *fn);
	~cRoomMan();

	virtual void Draw(const bool named);//флаг определяет: грузить ли имена объектов в стек
	virtual void pickItem(const int hit);
	void addScore(const int num);
	void subScore(const int num);

	int processTime();//3 состояния: 0 - порядок, 1 - выигрыш, 2 - проигрыш
	void setMaxTime(string val1, string val2, const int min, const int sec);
	string getMaxTime() { return maxTime; }

	void setTimer(const bool pause);
	bool getTimer();

	int getMin() { return timer->getMin(); }
	int getSec() { return timer->getSec(); }

	string getTitle() { return m_title; }
	bool getGameEnd() { return m_game_end; }
	void setGameEnd(const bool b) { m_game_end = b; }
};