/*
 * 
 * Made by NeoLTK
 * 
 */

#include "header.h"
extern bool buttonUP = true;

void controle(SceCtrlData pad, int *navOffset, bool *exit, Plugins plugins[]) {
	if (pad.buttons & SCE_CTRL_UP && buttonUP) {
		*navOffset -= 1;
		buttonUP = false;
	} else if (pad.buttons & SCE_CTRL_DOWN && buttonUP) {
		*navOffset += 1;
		buttonUP = false;
	} else if (pad.buttons & SCE_CTRL_CROSS && buttonUP) {
		bool curStat = plugins[*navOffset].active;
		plugins[*navOffset].active = (curStat == true ? false : true);
		putConfigs(plugins);
		dirPlugins(plugins, *navOffset);
		buttonUP = false;
	} else if (!pad.buttons) {
		buttonUP = true;
	}

	if (pad.buttons & SCE_CTRL_START) {
		*exit = true;
	}
}