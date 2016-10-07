/*
 * 
 * Made by NeoLTK with xerpi draw
 * 
 */

#include "header.h"

void init() {
	struct stat st = {0};

	if (stat(disablePath, &st) == -1) {
		sceIoMkdir(disablePath,  0777);
	}

	init_video();
}

void finish() {
	end_video();
	sceKernelExitProcess(0);
}

int main(int argc, char *argv[]) {
	init();

	SceUInt64 timer[2];
	timer[0] = 0;
	timer[1] = 0;

	SceCtrlData pad;
	Plugins pluginsList[50];

	getPlugins(pluginsList);
	getConfigs(pluginsList);

	int navOffset = 0;
	bool exit = false;
	char *version = "V0.3";

	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

	while(exit != true){
		timer[0] = sceKernelGetProcessTimeWide();
		sceCtrlPeekBufferPositive(0, &pad, 1);
		clear_screen();

		controle(pad, &navOffset, &exit, pluginsList, timer);
		menuDraw(pluginsList, &navOffset);		
		
		font_draw_stringf(0, 10, RGBA8(0, 255, 0, 255), "VITAPluginsManager by NeoLTK | %s ", version);

		swap_buffers();
		sceDisplayWaitVblankStart();
	}

	finish();
	return 0;
}
