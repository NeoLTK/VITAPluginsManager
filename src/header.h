/*
 * 
 * Made by NeoLTK with xerpi draw
 * 
 */
#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/io/dirent.h>
#include <psp2/io/stat.h>
#include <psp2/io/fcntl.h>

#include "utils.h"
#include "draw.h"

typedef struct manager Manager;

typedef struct plugins {
	Manager *pluginsManager;
	char *name;
	char *path;
	bool active;
	bool safe;
} Plugins;

typedef struct menu {
	char *title;
	void (*function)(Plugins *plugins);
} Menu;

typedef struct rightpanel {
	bool active;
	int navOffset;
	Menu *panelMenu;
} RightPanel;

struct manager {
	char *version;
	char *message;
	int navOffset;
	bool active;
	Plugins *plugins;
	RightPanel *rightPanel;
	SceCtrlData pad;
};




#define defaultPath     ((char *) "ux0:/plugins/")
#define disablePath     ((char *) "ux0:/plugins_disabled/")
#define configsPath     ((char *) "ux0:/plugins/game.txt")
#define version     ((char *) "0.6")


void securityCheck(Plugins *plugins);
void menuDraw(Manager *pluginsManager);
void uiDraw(Manager *pluginsManager);
void getPlugins(Manager *pluginsManager);
void getConfigs(Plugins plugins[]);
void dirPlugins(Manager *pluginsManager);
void putConfigs(Plugins plugins[]);
void enablePlugins(Plugins *plugins);
void disablePlugins(Plugins *plugins);
void controle(Manager *pluginsManager);

#endif