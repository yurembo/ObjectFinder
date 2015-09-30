#include "cDBman.h"

cDBman::cDBman()
{
	isOpenDB = false;
	dbfile = NULL;
	ConnectDB();
}

cDBman::~cDBman()
{
	DisconnectDB();
	isOpenDB = false;
	dbfile = NULL;
}

bool cDBman::ConnectDB()
{
	if (sqlite3_open(DB, &dbfile) == SQLITE_OK)
	{
		isOpenDB = true;
		return true;
	}		 

	return false;
}

void cDBman::DisconnectDB()
{
	if (isOpenDB == true) 
	{
		sqlite3_close(dbfile);
	}
}

UserData cDBman::getUserData(const string username)
{
	sqlite3_stmt *statement;	
	UserData ud = { "", 0, 0, "", "" };

	char *query = "select * from users_table";

	if (sqlite3_prepare(dbfile, query, -1, &statement, 0) == SQLITE_OK) 
	{
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

			res = sqlite3_step(statement);

			if (res == SQLITE_ROW) 
			{
				char *ch = (char*)sqlite3_column_text(statement, 1);
				if (ch != NULL) 
					ud.name = ch; 

				ch = (char*)sqlite3_column_text(statement, 2);
				if (ch != NULL) 
					ud.energy = atoi(ch); 
				else ud.energy = 0;

				ch = (char*)sqlite3_column_text(statement, 3);
				if (ch != NULL) 
					ud.maxEnergy = atoi(ch); 
				else ud.maxEnergy = 0;

				ch = (char*)sqlite3_column_text(statement, 4);
				if (ch != NULL) 
					ud.time_in = ch;

				ch = (char*)sqlite3_column_text(statement, 5);
				if (ch != NULL) 
					ud.time_out = ch;
			}			
	}
	return ud;
}

RoomData cDBman::getRoomData(const string title)
{
	sqlite3_stmt *statement;	
	RoomData rd = { "", 0, "" };

	string q = "select * from rooms_table where room = '" + title + "'";
	const char *query = q.c_str();

	if (sqlite3_prepare(dbfile, query, -1, &statement, 0) == SQLITE_OK) 
	{
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

			res = sqlite3_step(statement);

			if (res == SQLITE_ROW) 
			{
				char *ch = (char*)sqlite3_column_text(statement, 1);
				if (ch != NULL) 
					rd.title = ch; 
				else rd.energy = 0;

				ch = (char*)sqlite3_column_text(statement, 2);
				if (ch != NULL) 
					rd.energy = atoi(ch); 
				else rd.energy = 0;

				ch = (char*)sqlite3_column_text(statement, 3);
				if (ch != NULL) 
					rd.time_rec = ch; 
			}			
	}
	return rd;
}

void cDBman::setUserData(const UserData data)
{
	char energy[10];
	_itoa_s(data.energy, energy, 10, 10);
	string str = "update users_table set energy = '";
	str.append(energy);
	str.append("', time_in = '");
	str.append(data.time_in);
	str.append("', time_out = '");
	str.append(data.time_out);
	str.append("' where name = '");
	str.append(USER_NAME);
	str.append("'");
	const char *query = str.c_str();	

	sqlite3_stmt *statement;
	
	if (sqlite3_prepare(dbfile, query, -1, &statement, 0) == SQLITE_OK)
	{
		int result = sqlite3_step(statement);
		sqlite3_finalize(statement);
	}
}

void cDBman::setRoomData(const RoomData data)
{
	if (data.energy == 0) return;

	string str = "update rooms_table set ";
	str.append("time_record = '");
	str.append(data.time_rec);
	str.append("' where room = '");
	str.append(data.title);
	str.append("'");
	const char *query = str.c_str();	

	sqlite3_stmt *statement;
	
	if (sqlite3_prepare(dbfile, query, -1, &statement, 0) == SQLITE_OK)
	{
		int result = sqlite3_step(statement);
		sqlite3_finalize(statement);
	}
}