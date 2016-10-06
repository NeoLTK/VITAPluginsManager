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
#include <psp2/touch.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/io/dirent.h>
#include <psp2/io/stat.h>

#include "utils.h"
#include "draw.h"

typedef struct plugins {
	char *name;
	char *path;
	bool active;
} Plugins;

extern char *defaultPath = "ux0:/plugins/";
extern char *disablePath = "ux0:/plugins_disabled/";
extern char *configsPath = "ux0:/plugins/game.txt";

void menuDraw(Plugins plugins[], int *navOffset);
void getPlugins (Plugins plugins[]);
void getConfigs(Plugins plugins[]);
void dirPlugins(Plugins plugins[], int offset);
void putConfigs (Plugins plugins[]);
void controle(SceCtrlData pad, int *navOffset, bool *exit, Plugins plugins[], SceUInt64 *timer);

#endif