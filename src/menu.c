/*
 * 
 * Made by NeoLTK with xerpi draw
 * 
 */

#include "header.h"

void uiDraw(){
	font_draw_string(20, 10, RGBA8(0, 255, 0, 255), "Plugins Name");
	font_draw_string(775, 10, RGBA8(0, 255, 0, 255), "Status");
	draw_rectangle(0, 35, 960, 1, GREEN);

	draw_rectangle(0, 510, 960, 1, GREEN);
	font_draw_stringf(5, 520, RGBA8(0, 255, 0, 255), "VITAPluginsManager |%s", version);
	font_draw_string(SCREEN_W - 130, 520, RGBA8(0, 255, 0, 255), "-|NeoLTK");
}

uint32_t epileptik (){
	static bool offset = true;
    static uint32_t value = 0;

	if (value < 255 && offset)
		return value = value + 3;
	else if (value > 0 && !offset)
		return value = value - 3;
	else if (value == 0)
		offset = true;
	else if (value == 255)
		offset = false;

	return value;
}

void menuDraw(Plugins plugins[], int *navOffset) {
	int i;
	for (i = 0;  plugins[i].name != '\0'; i++) 
		continue;

	int size = i;
	uint32_t epileptikColor = epileptik();

	if (size > 0) {
		if (*navOffset > size-1) {
			*navOffset = 0;
		} else if (*navOffset < 0) {
			*navOffset = size-1;
		}

		for (int i = 0; plugins[i].name != '\0'; i++) {

			if (*navOffset == i) {
				font_draw_string(20, 55 + (i * 25), RGBA8(epileptikColor, epileptikColor, epileptikColor, 255), "*");
				font_draw_string(50, 55 + (i * 25), RGBA8(255, 255, 255, 255), plugins[i].name);
				font_draw_string(750, 55 + (i * 25), RGBA8(255, 255, 255, 255), (plugins[i].active ? "[ENABLED]" : "[DISABLED]"));
				font_draw_string(925, 55 + (i * 25), RGBA8(epileptikColor, epileptikColor, epileptikColor, 255), "*");

			} else {
				font_draw_string(50, 55 + (i * 25), RGBA8(0, 255, 0, 255),  plugins[i].name);
				font_draw_string(750, 55 + (i * 25), RGBA8(0, 255, 0, 255), (plugins[i].active ? "[ENABLED]" : "[DISABLED]"));
			}
		}
	}


	uiDraw();
}

