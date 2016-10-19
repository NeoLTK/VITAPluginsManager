/*
 * 
 * Made by NeoLTK
 * 
 */

#include "header.h"



void mainControle(Manager *pluginsManager, bool *buttonUP) {
	SceCtrlData *pad = &(pluginsManager->pad);
	RightPanel *rightPanel = pluginsManager->rightPanel;

	if (pad->buttons & SCE_CTRL_UP && *buttonUP && !rightPanel->active) {
		pluginsManager->navOffset -= 1;
		*buttonUP = false;
	} 
	else if (pad->buttons & SCE_CTRL_DOWN && *buttonUP && !rightPanel->active) {
		pluginsManager->navOffset += 1;
		*buttonUP = false;
	} 
	else if (pad->buttons & SCE_CTRL_CROSS && *buttonUP && !rightPanel->active) {
		dirPlugins(pluginsManager);
		putConfigs(pluginsManager->plugins);
		*buttonUP = false;
	} 
}

void rightPanelControle(Manager *pluginsManager, bool *buttonUP) {
	RightPanel *rightPanel = pluginsManager->rightPanel;
	SceCtrlData *pad = &(pluginsManager->pad);

	if (pad->buttons & SCE_CTRL_UP && *buttonUP && rightPanel->active) {
		rightPanel->navOffset -= 1;
		*buttonUP = false;
	} 
	else if (pad->buttons & SCE_CTRL_DOWN && *buttonUP && rightPanel->active) {
		rightPanel->navOffset += 1;
		*buttonUP = false;
	} 
	else if (pad->buttons & SCE_CTRL_CROSS && *buttonUP && rightPanel->active) {
		int offset = rightPanel->navOffset;
		int offsetP = pluginsManager->navOffset;

		rightPanel->panelMenu[offset].function(pluginsManager->plugins + offsetP);
		
		rightPanel->active = false;
		*buttonUP = false;
	}

	if (pad->buttons & SCE_CTRL_TRIANGLE  && *buttonUP){
		rightPanel->active = (rightPanel->active ? false : true);
		*buttonUP = false;
	}
}

void controle(Manager *pluginsManager) {
	static bool buttonUP = true;
	SceCtrlData *pad = &(pluginsManager->pad);


	mainControle(pluginsManager, &buttonUP);
	rightPanelControle(pluginsManager, &buttonUP);

	if (pad->buttons & SCE_CTRL_START)
		pluginsManager->active = false;

	if (!pad->buttons)
		buttonUP = true;

}