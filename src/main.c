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

int putPlugins(Plugins plugins[], SceIoDirent item, int offset){
	char *defaultPath = "ux0:/plugins/";

	if (strstr(item.d_name, "suprx") != NULL) {
    	plugins[offset].name = malloc(sizeof(char) * strlen(item.d_name));
    	strcpy(plugins[offset].name, item.d_name);

    	plugins[offset].path = malloc(sizeof(char) * (strlen(defaultPath) + (strlen(plugins[offset].name))));
    	strcpy(plugins[offset].path, defaultPath);
    	strcat(plugins[offset].path, plugins[offset].name);

		plugins[offset].active = malloc(sizeof(bool));
    	plugins[offset].active = false;
		return 1;
	}

	return 0;
}

void getPlugins (Plugins plugins[]) {
	struct SceIoDirent dir;
	int offset = 0;
	int fd;
	char *path[2];
	path[0] = "ux0:/plugins/";
	path[1] = "ux0:/data/";
	

	for (int i = 0; i <= 1; i++) {
		fd = sceIoDopen(path[i]);
		if (fd >= 0) {
			while(sceIoDread(fd, &dir)) 
        		offset = offset + putPlugins(plugins, dir, offset);

		    sceIoDclose(fd);
		}
		
	    plugins[offset].name = malloc(sizeof(char));
	   	plugins[offset].name = '\0';
	}
}


void getConfigs(Plugins plugins[]){
	FILE* fp;
	bool next = false;
	const size_t lineNB = 50;
	char* line = malloc(lineNB);

	for (int i = 0; plugins[i].name != '\0'; i++) {
		fp = fopen("ux0:/plugins/game.txt", "r");

		if (fp != NULL) {
			next = false;
			while (fgets(line, lineNB, fp) != NULL && next != true)  {
		    	if (strstr(line, plugins[i].name) != NULL){
		    		char *token = strtok(line, " ");
		    		if (token != NULL){
		    			token = strtok(NULL, " ");
		    			if (token != NULL){
		    				if (strstr(token, "1") != NULL){
		    					plugins[i].active = true;
		    					next = true;
		    				} else plugins[i].active = false;
		    			} else plugins[i].active = false;
		    		} else plugins[i].active = false;
		    	} else plugins[i].active = false;
			}
			fclose(fp);
		}
	}
	free(line);
}

void dirPlugins(Plugins plugins[], int offset) {
	char *disablePath = "ux0:/data/";
	char *tmp = malloc(sizeof(char) * (strlen(disablePath) + strlen(plugins[offset].name)));
	struct stat st = {0};

	strcpy(tmp, disablePath);
	strcat(tmp, plugins[offset].name);

	if (plugins[offset].active == true){
		if (stat(plugins[offset].path, &st) == -1) {
			rename (tmp, plugins[offset].path);
		}
	} else {
		if (stat(plugins[offset].path, &st) != -1) {
			rename (plugins[offset].path, tmp);
		}
	}

	free(tmp);
}

void putConfigs (Plugins plugins[]){
	FILE* fp = fopen("ux0:/plugins/game.txt", "w");

	if (fp != NULL){
		for (int i = 0; plugins[i].name != '\0'; i++) {
			fprintf(fp, "%s %d\n", plugins[i].path, (plugins[i].active ? 1 : 0));
		}

		fclose(fp);
	}

}

void controle(SceCtrlData pad, int *navOffset, bool *exit, Plugins plugins[], SceUInt64 *timer){
	if (timer[0] >= (timer[3] + 100000)) {
		if (pad.buttons & SCE_CTRL_UP) {
			*navOffset -= 1;
		} else 	if (pad.buttons & SCE_CTRL_DOWN) {
			*navOffset += 1;
		}

		if (pad.buttons & SCE_CTRL_CROSS) {
			bool curStat = plugins[*navOffset].active;
			plugins[*navOffset].active = (curStat == true ? false : true);
			putConfigs(plugins);
			dirPlugins(plugins, *navOffset);
		}

		if (pad.buttons & SCE_CTRL_START) {
			*exit = true;
		}

		timer[3] = timer[0];
	}
}

int main(int argc, char *argv[]) {
	init_video();

	SceUInt64 timer[4];
	timer[0] = 0;
	timer[1] = 0;
	timer[2] = 0;
	timer[3] = 0;

	SceCtrlData pad;
	Plugins pluginsList[50];

	getPlugins(pluginsList);
	getConfigs(pluginsList);

	int navOffset = 0;
	bool exit = false;
	char *version = "V0.2";

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

	end_video();
	sceKernelExitProcess(0);
	return 0;
}
