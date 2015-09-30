#include <time.h>
//функции для работы с преобразованием времени (длинный формат)

string getStrNowTime()
{
	string res;
	time_t rawtime;
	tm *timeinfo;
	char buffer[100];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 100, "%m/%d/%Y %H/%M/%S %w/%j", timeinfo);
	res.assign(buffer);

	return res;
}

tm *getTmNowTime()
{
	string res;
	time_t rawtime;
	tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return timeinfo;
}

tm getTmTimeFromStr(string strTime)
{
	tm dt;
	memset(&dt, 0, sizeof(dt));
	unsigned int i = 0, numpart = 0;
	vector<string>part;
	string str = "";

	for (i = 0; i < strTime.length(); i++) {
		char ch = strTime[i];
		if (strncmp(&ch, "/", 1) != 0 && strncmp(&ch, ":", 1) != 0 && strncmp(&ch, " ", 1) != 0) {
			str = str + ch;
			if (i == strTime.length() - 1)
				part.push_back(str);
		} else 
		if (strncmp(&ch, "/", 1) == 0 || strncmp(&ch, ":", 1) == 0) {
			part.push_back(str);
			str = "";
		} else
		if (strncmp(&ch, " ", 1) == 0) {
			part.push_back(str);
			if (numpart == 0)
			{
				dt.tm_mon = atoi(part.at(0).c_str());
				dt.tm_mday = atoi(part.at(1).c_str());
				string s = part.at(2);
				s.erase(0, 2);
				s.insert(0, "1");
				dt.tm_year = atoi(s.c_str());
			} else if (numpart == 1) {
				dt.tm_hour = atoi(part.at(0).c_str());
				dt.tm_min = atoi(part.at(1).c_str());
				dt.tm_sec = atoi(part.at(2).c_str());
			}
			part.clear();
			str = "";
			numpart++;
		}
	}

	dt.tm_wday = atoi(part.at(0).c_str());
	dt.tm_yday = atoi(part.at(1).c_str());
	dt.tm_mon--;
	dt.tm_yday--;

return dt;
}