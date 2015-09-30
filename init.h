#pragma once

#undef _UNICODE

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#include <stdio.h>
#include <string>

using namespace std;

static int WinWidth = 1000;
static int WinHeight = 900;

const float TEX_MOV_SPEED = 0.03;

static void* FONT = GLUT_BITMAP_TIMES_ROMAN_24;

const string USER_NAME = "user1";//единственный пользователь

const int g_time_redraw = 30;
const int g_time_process = 1000;
const int g_time_appenergy = 3000;
const int g_max_sec = 59;

//room
const string ROOM = "room";
const string KITCHEN = "kitchen";

//dialogs
const string PAUSE = "pause";
const string WIN = "win";
const string LOSS = "loss";
const string FEWENERGY = "fewEnergy";