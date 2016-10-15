/*
 * 
 * Made by NeoLTK
 * 
 */

#include "header.h"

void controle(Manager *pluginsManager) {
	static bool buttonUP = true;
	SceCtrlData pad = pluginsManager->pad;

	if (pad.buttons & SCE_CTRL_UP && buttonUP && !pluginsManager->rightPanel->active) {
		pluginsManager->navOffset -= 1;
		buttonUP = false;
	} 
	else if (pad.buttons & SCE_CTRL_DOWN && buttonUP && !pluginsManager->rightPanel->active) {
		pluginsManager->navOffset += 1;
		buttonUP = false;
	} 
	else if (pad.buttons & SCE_CTRL_CROSS && buttonUP && !pluginsManager->rightPanel->active) {
		dirPlugins(pluginsManager);
		putConfigs(pluginsManager->plugins);
		buttonUP = false;
	} 



	if (pad.buttons & SCE_CTRL_UP && buttonUP && pluginsManager->rightPanel->active) {
		pluginsManager->rightPanel->navOffset -= 1;
		buttonUP = false;
	} 
	else if (pad.buttons & SCE_CTRL_DOWN && buttonUP && pluginsManager->rightPanel->active) {
		pluginsManager->rightPanel->navOffset += 1;
		buttonUP = false;
	} 
	else if (pad.buttons & SCE_CTRL_CROSS && buttonUP && pluginsManager->rightPanel->active) {
		int offset = pluginsManager->rightPanel->navOffset;
		pluginsManager->rightPanel->panelMenu[offset].function(pluginsManager->plugins + offset);
		buttonUP = false;
	}




	if (pad.buttons & SCE_CTRL_TRIANGLE  && buttonUP){
		pluginsManager->rightPanel->active = (pluginsManager->rightPanel->active ? false : true);
		buttonUP = false;
	}

	if (pad.buttons & SCE_CTRL_START)
		pluginsManager->active = false;

	if (!pad.buttons)
		buttonUP = true;

}
