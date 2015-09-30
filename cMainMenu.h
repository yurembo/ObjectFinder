//класс главного меню
#pragma once

#include "init.h"
#include "cItemList.h"

class cMainMenu
{
private:
	cTexture *m_title;
	cTexture *m_room_button;
	cTexture *m_kitchen_button;

public:
	cMainMenu();
	~cMainMenu();

	void Draw(const bool named);
};