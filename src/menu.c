/*
 * 
 * Made by NeoLTK with xerpi draw
 * 
 */

#include "header.h"

void uiDraw(){
	font_draw_string(20, 10, RGBA8(0, 255, 0, 255), "Plugins Name");
	font_draw_string(775, 10, RGBA8(0, 255, 0, 255), "Status  |(/\\");
	draw_rectangle(0, 35, 960, 1, GREEN);

	draw_rectangle(0, 510, 960, 1, GREEN);
	font_draw_stringf(5, 520, RGBA8(0, 255, 0, 255), "VITAPluginsManager |%s", version);
	font_draw_string(SCREEN_W - 130, 520, RGBA8(0, 255, 0, 255), "-|NeoLTK");
}

uint32_t epileptik (){
	static bool flag = true;
    static uint32_t offset = 0;

	if (offset < 255 && flag)
		return offset = offset + 3;
	else if (offset > 0 && !flag)
		return offset = offset - 3;
	else if (offset == 0)
		flag = true;
	else if (offset == 255)
		flag = false;

	return offset;
}

void rightPanel(RightPanel *panel, int size){
	static int offset = 0;
	static int x = 960;
	static int y = 36;
	static int w = 0;
	static int h = 474;
	int baseX = 960;
	int p = (offset * size) / 100;
	
	x = baseX - p;
	w = p;

	if (panel->active && offset < 100) offset = offset + 10;
	else if (!panel->active && offset > 0) offset = offset - 10;

	if (panel->navOffset > sizeof(panel->panelMenu) -1) {
		panel->navOffset = 0;
	} else if (panel->navOffset < 0) {
		panel->navOffset = sizeof(panel->panelMenu) -1;
	}
	
	draw_rectangle(x, y, w, h, DARKGREY);

	if (offset == 100) {
		for (int i = 0; i != sizeof(panel->panelMenu) - 1; i++){
			if (panel->navOffset == i)
				font_draw_string(740, 45 + i * 25, RGBA8(255, 255, 255, 255), panel->panelMenu[i].title);
			else
				font_draw_string(740, 45 + i * 25, RGBA8(0, 255, 0, 255), panel->panelMenu[i].title);
		}
	}

}

void menuDraw(Manager *pluginsManager) {
	int i;
	for (i = 0;  pluginsManager->plugins[i].name != '\0'; i++) 
		continue;

	int size = i;
	uint32_t eC = epileptik();

	if (size > 0) {
		if (pluginsManager->navOffset > size-1) {
			pluginsManager->navOffset = 0;
		} else if (pluginsManager->navOffset < 0) {
			pluginsManager->navOffset = size-1;
		}


		for (int i = 0; pluginsManager->plugins[i].name != '\0'; i++) {

			if (pluginsManager->navOffset == i) {
				font_draw_string(20, 55 + (i * 25), RGBA8(eC, eC, eC, 255), "*");
				font_draw_string(925, 55 + (i * 25), RGBA8(eC, eC, eC, 255), "*");

				font_draw_string(50, 55 + (i * 25), RGBA8(255, 255, 255, 255), pluginsManager->plugins[i].name);
				font_draw_string(750, 55 + (i * 25), RGBA8(255, 255, 255, 255), (pluginsManager->plugins[i].active ? "[ENABLED]" : "[DISABLED]"));

			} else {
				font_draw_string(50, 55 + (i * 25), RGBA8(0, 255, 0, 255),  pluginsManager->plugins[i].name);
				font_draw_string(750, 55 + (i * 25), RGBA8(0, 255, 0, 255), (pluginsManager->plugins[i].active ? "[ENABLED]" : "[DISABLED]"));
			}

			if (pluginsManager->plugins[i].safe == false)
				font_draw_string(945, 55 + (i * 25), RGBA8(255, 0, 0, 255), "*");

		}

	}

	uiDraw();
	rightPanel(pluginsManager->rightPanel, 250);
}




