/*
 * 
 * Made by NeoLTK with xerpi draw
 * 
 */

#include "header.h"

void menuDraw(Plugins plugins[], int *navOffset) {
	int i;
	for (i = 0;  plugins[i].name != '\0'; i++) 
		continue;

	int size = i;

	if (size > 0) {
		if (*navOffset > size-1) {
			*navOffset = 0;
		} else if (*navOffset < 0) {
			*navOffset = size-1;
		}

		for (int i = 0; plugins[i].name != '\0'; i++) {

			if (*navOffset == i) {
				font_draw_string(25, 35 + (i * 25), RGBA8(255, 255, 255, 255), plugins[i].name);
				font_draw_string(355, 35 + (i * 25), RGBA8(255, 255, 255, 255), (plugins[i].active == true ? "[ENABLED]" : "[DISABLED]"));

			} else {
				font_draw_string(20, 35 + (i * 25), RGBA8(0, 255, 0, 255),  plugins[i].name);
				font_draw_string(350, 35 + (i * 25), RGBA8(0, 255, 0, 255), (plugins[i].active == true ? "[ENABLED]" : "[DISABLED]"));
			}
		}
	}
}