#include "cMainMenu.h"

cMainMenu::cMainMenu()
{
	float xy[8];
	xy[0] = -1.0;
	xy[1] = 0.0;
	xy[2] = 1.0;
	xy[3] = 0.0;
	xy[4] = 1.0;
	xy[5] = 1.0;
	xy[6] = -1.0;
	xy[7] = 1.0;
	m_title = new cTexture(2, "title", xy, 0, 0, 640, 300, "mainmenu\\ObjectFinderTitle.png");

	float xy1[8];
	xy1[0] = -0.9;
	xy1[1] = -0.4;
	xy1[2] = -0.6;
	xy1[3] = -0.4;
	xy1[4] = -0.6;
	xy1[5] = -0.2;
	xy1[6] = -0.9;
	xy1[7] = -0.2;
	m_room_button = new cTexture(3, "room_button", xy1, 0, 0, 100, 50, "mainmenu\\room_button.png");

	float xy2[8];
	xy2[0] = 0.6;
	xy2[1] = -0.4;
	xy2[2] = 0.9;
	xy2[3] = -0.4;
	xy2[4] = 0.9;
	xy2[5] = -0.2;
	xy2[6] = 0.6;
	xy2[7] = -0.2;

	m_kitchen_button = new cTexture(4, "room_button", xy2, 0, 0, 100, 50, "mainmenu\\kitchen_button.png");
}

cMainMenu::~cMainMenu()
{
	if (m_title != NULL) {
		m_title->cleanTexMemory();
		delete m_title;
		m_title = NULL;
	}
	if (m_room_button) {
		m_room_button->cleanTexMemory();
		delete m_room_button;
		m_room_button = NULL;
	}
	if (m_kitchen_button) {
		m_kitchen_button->cleanTexMemory();
		delete m_kitchen_button;
		m_kitchen_button = NULL;
	}
}

void cMainMenu::Draw(const bool named)
{
	if (m_title != NULL) 
		m_title->drawQuad(false);
	if (m_room_button != NULL) 
		m_room_button->drawQuad(named);
	if (m_kitchen_button != NULL) 
		m_kitchen_button->drawQuad(named);
}