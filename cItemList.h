#include "cRoomMan.h"

const float step = 0.35;

//������ ���������
class cItemList : public cRoomMan
{
public:
	cItemList();
	cItemList(const char *ch);
	~cItemList();

	void Draw();
	void pickItem(const int hit);
};