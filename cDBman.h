#pragma once

#include "init.h"
#include "sqlite3.h"
#include "userData.h"

#define DB "gameDB.s3db"

class cDBman
{
private:
	bool isOpenDB;
	sqlite3 *dbfile;

public:
	cDBman();
	~cDBman();

	void setOpenDB(const bool b) { isOpenDB = b; }
	bool getOpenDB() { return isOpenDB; }
	sqlite3 *getDBfile() { return dbfile; }
	bool ConnectDB();
	void DisconnectDB();

	UserData getUserData(const string username);
	RoomData getRoomData(const string title);

	void setUserData(const UserData data);
	void setRoomData(const RoomData data);
};