//ObjectFinder developed by Yuriy Yazev

#include "cMainMenu.h"
#include "cDlgMan.h"
#include "cDBman.h"
#include "TimeMan.h"

cMainMenu *mainmenu = NULL;
cRoomMan *room = NULL;
cItemList *list = NULL;
cDlgMan *dlg = NULL;
cDBman *db = NULL;
cLabel *energyLab = NULL;
UserData userdata = { "", 0, 0, "", "" };
RoomData roomdata = { "", 0, "" };

//useful function
string getTimeRec(const string str)
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

void outputEnergy()
{
	if (energyLab != NULL) {
		char e[10];
		char me[10];
		_itoa_s(userdata.energy, e, 10, 10);
		_itoa_s(userdata.maxEnergy, me, 10, 10);
		string str = "";
		str.append(e);
		str.append("/");
		str.append(me);

		char energyStr[50];
		string s = "Energy: " + str;
		memset(energyStr, 0, sizeof(energyStr));
		strncpy_s(energyStr, 50, s.c_str(), sizeof(energyStr) - 1);
		energyLab->OutputLabel(energyStr);
	}
}

void Display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mainmenu != NULL) mainmenu->Draw(false);
	if (room != NULL) room->Draw(false);
	if (list != NULL) list->Draw();
	if (dlg != NULL) {
		dlg->Draw(false);
		dlg->DrawLabel();
	}
	outputEnergy();
	glutSwapBuffers();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(g_time_redraw, Timer, 1);
}

void getUppEnergy()
{
	long unitApp = 0;
	long newEnergy = 0;

	  userdata.time_in = getStrNowTime();
	  if (userdata.time_out != "") {
		  tm dt = getTmTimeFromStr(userdata.time_out);
		  tm *now = getTmNowTime();
		  time_t s_now = mktime(now);
		  time_t s_dt = mktime(&dt);
		  time_t diffsec = difftime(s_now, s_dt);
		  unitApp = diffsec / (g_time_appenergy / 1000);
		  newEnergy = userdata.energy + unitApp;
		  if (newEnergy > userdata.maxEnergy) newEnergy = userdata.maxEnergy;
	  } else {
		  unitApp = 0;
		  newEnergy = userdata.maxEnergy;
	  }
	  userdata.energy = newEnergy;
}

void Init()
{
	  glEnable(GL_DEPTH_TEST);
	  glEnable(GL_LIGHTING);
	  glEnable(GL_LIGHT0);//свет нужен для блендинга

	  ilInit();
	  iluInit();
	  ilutRenderer(ILUT_OPENGL);
	  ilEnable(IL_ORIGIN_SET);
	  ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
  	
	  ilEnable(IL_TYPE_SET);
	  ilTypeFunc(IL_UNSIGNED_BYTE);
  	
	  ilEnable(IL_FORMAT_SET);
	  ilFormatFunc(IL_RGB); 

	  db = new cDBman();
	  userdata = db->getUserData(USER_NAME);//передаем имя юзера
	  mainmenu = new cMainMenu();

	  getUppEnergy();

	  int pos_col[5] = { WinWidth / 2, WinHeight - 30, 255, 255, 255 };
	  energyLab = new cLabel(FONT, pos_col);
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	WinWidth = width;			
	WinHeight = height;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, GLfloat(WinWidth) / WinHeight, 1, 10);
	
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -3.0);

	glutPostRedisplay();
}

int Selection(const int x, const int y)	//выборка объекта										
{
	GLuint buffer[512];										
	GLint hits = 0;												

	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(sizeof(buffer), buffer);
	glDisable(GL_TEXTURE_2D);
	glRenderMode(GL_SELECT);

	glInitNames();											
	glPushName(0);											
	
	glMatrixMode(GL_PROJECTION);							
	glPushMatrix();											
	glLoadIdentity();									

	gluPickMatrix((GLdouble)x, (GLdouble) (viewport[3]-y), 1.0f, 1.0f, viewport);

	gluPerspective(45.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.1f, 10.0f);
	glMatrixMode(GL_MODELVIEW);					

	if (room != NULL && dlg == NULL) room->Draw(true);			
	if (mainmenu != NULL) mainmenu->Draw(true);
	if (dlg != NULL) dlg->Draw(true);

	glMatrixMode(GL_PROJECTION);						
	glPopMatrix();										
	glMatrixMode(GL_MODELVIEW);	
	hits = glRenderMode(GL_SELECT);			
	glRenderMode(GL_RENDER);		
	glEnable(GL_TEXTURE_2D);

	if (hits > 0)										
	{
		int	choose = 0;
		if (dlg != NULL) {
			choose = buffer[7];
			goto jump;
		} else
		if (room != NULL) choose = buffer[7]; else
		if (mainmenu != NULL) choose = buffer[3];
jump:
		if (choose < 0)//выбран фон
			return 1;				
		return choose;	
    }
	return hits;
}

void startLivingRoom()
{
	if (room == NULL)
		room = new cRoomMan(ROOM, "rooms\\LivingRoom\\LivingRoom.xml");

	if (list == NULL)
		list = new cItemList("rooms\\LivingRoom\\LivingRoomList.xml");
}

void startKitchen()
{
	if (room == NULL)
		room = new cRoomMan(KITCHEN, "rooms\\Kitchen\\Kitchen.xml");

	if (list == NULL)
		list = new cItemList("rooms\\Kitchen\\KitchenList.xml");
}

void deleteMainMenu()
{
	if (mainmenu != NULL) {
		delete mainmenu;
		mainmenu = NULL;
	}
}

void deleteDlg()
{
	if (dlg != NULL) {
		delete dlg;
		dlg = NULL;
	}
}

void deleteRoom()
{
	if (room != NULL) {
		delete room;
		room = NULL;
	}
}

void deleteList()
{
	if (list != NULL) {
		delete list;
		list = NULL;
	}
}

bool getRecordFromDlg()
{
	if (dlg != NULL && (dlg->getTitle() == WIN || dlg->getTitle() == PAUSE)) {
		roomdata.time_rec = dlg->getRecord();
		db->setUserData(userdata);
		db->setRoomData(roomdata);
		return true;
	}
	return false;
}

void processDlg(const int hit)
{
	switch (hit) {
		case 2 :
			getRecordFromDlg();
			deleteDlg();
			deleteRoom();
			deleteList();
			mainmenu = new cMainMenu();
			break;
		case 3 :
			getRecordFromDlg();
			deleteDlg();
			room->setTimer(true);
			break;
	}
}

bool getPlay(const string title)
{
	roomdata = db->getRoomData(title);
	bool back = false;
	if (userdata.energy >= roomdata.energy) back = true;

	return back;
}

void pickUp(const int x, const int y)
{
	int hit = Selection(x, y);
	if (hit > 1) {
		if (dlg != NULL) {
				processDlg(hit);
				return;
		}else
		if (room != NULL) room->pickItem(hit); 
		if (list != NULL) list->pickItem(hit);
		if (mainmenu != NULL) {
			switch (hit) {
				case 3 :
					if (getPlay(ROOM)) {
						userdata.energy -= roomdata.energy;
						deleteMainMenu();
						startLivingRoom();
					} else 
						dlg = new cDlgMan(FEWENERGY, userdata.energy, roomdata.energy);
					break;
				case 4 :
					if (getPlay(KITCHEN)) {
						userdata.energy -= roomdata.energy;
						deleteMainMenu();
						startKitchen();
					} else dlg = new cDlgMan(FEWENERGY, userdata.energy, roomdata.energy);
					break;
			}
		}
	}else 
		if (hit == 1) 
			if (room != NULL && dlg == NULL) room->subScore(2);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case VK_ESCAPE:
			if (room != NULL) {
				if (dlg == NULL) {
					string maxTime = room->getMaxTime();
					dlg = new cDlgMan(PAUSE, getTimeRec(maxTime), getTimeRec(roomdata.time_rec));
					room->setTimer(false);
					getRecordFromDlg();
				} else {
					getRecordFromDlg();
					room->setTimer(true);
					deleteDlg();
				}
			}
				break;
	}
}

void MouseClick(int button, int state, int x, int y)//Обработка щелчков мыши
{
	if (button == GLUT_LEFT_BUTTON)//Левая кнопка
	{
		switch (state)
		{
			case GLUT_DOWN:				
				pickUp(x, y);
				break;
		}
	}
}

void processTime(int val)
{
	int i = 0;
	if (room != NULL) {
		i = room->processTime();
		if (i > 0) {
			room->setTimer(false);
			if (dlg == NULL) {
				if (i == 1) {
					if (!room->getGameEnd()) {
						room->setGameEnd(true);
						//roomdata.time_rec = dlg->getRecord();
						dlg = new cDlgMan(WIN, room->getMin(), room->getSec(), getTimeRec(room->getMaxTime()), getTimeRec(roomdata.time_rec));
					}
				} else if (i == 2) {
					if (!room->getGameEnd()) {
						room->setGameEnd(true);
						dlg = new cDlgMan(LOSS);
					}
				}
			}
		}
	}

	glutTimerFunc(g_time_process, processTime, 1);
}

LRESULT CALLBACK WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
		case WM_DESTROY:          
			if (db != NULL) {
				userdata.time_out = getStrNowTime();
				if (!getRecordFromDlg()) {
					db->setUserData(userdata);
					db->setRoomData(roomdata);
				}
			}
			exit(0);
		    PostQuitMessage(0);
		    return 0;

         case WM_KEYUP:
             Keyboard(wparam, 0, 0);
			 return 0;
 
        case WM_SIZE: 
            Reshape(LOWORD(lparam), HIWORD(lparam));
            return 0; 

		 case WM_LBUTTONDOWN:
			 MouseClick(GLUT_LEFT_BUTTON, GLUT_DOWN, LOWORD(lparam), HIWORD(lparam));
			 return 0;

			case WM_SETCURSOR:
				glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
			return 0;
    
		default:
		    return DefWindowProc(wnd, msg, wparam, lparam);
	}
}

void appUserEnergy(int val)
{
	//if (room != NULL && room->getTimer()) {
		if (userdata.energy < userdata.maxEnergy)
			userdata.energy += 1;
	//}

	glutTimerFunc(g_time_appenergy, appUserEnergy, 1);
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN)-WinWidth)/2, (GetSystemMetrics(SM_CYSCREEN)-WinHeight)/2);
	glutCreateWindow("ObjectFinder");	

	HWND m_window = FindWindowA(NULL, "ObjectFinder");
    SetWindowLong(m_window, GWL_WNDPROC, (LONG)WindowProc);

	glutDisplayFunc(Display);

	Init();
	glutTimerFunc(g_time_redraw, Timer, 1);
	glutTimerFunc(g_time_process, processTime, 1);
	glutTimerFunc(g_time_appenergy, appUserEnergy, 1);
	glutMainLoop();

	return 0;
}