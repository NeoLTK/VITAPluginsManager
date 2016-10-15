/*
 * 
 * Made by NeoLTK
 * 
 */

#include "header.h"

void putConfigs (Plugins plugins[]){
	sceIoRemove(configsPath);
	SceUID fp = sceIoOpen(configsPath, SCE_O_WRONLY | SCE_O_CREAT, 0777);
	char *path;

	if (fp >= 0){
		for (int i = 0; plugins[i].name != '\0'; i++) {
			path = malloc(sizeof(char) * (strlen(defaultPath) + strlen(plugins[i].name) + 4));
			strcpy(path, defaultPath);
			strcat(path, plugins[i].name);
			strcat(path, " 1\n");

			if (plugins[i].active)
				sceIoWrite(fp, path, strlen(path));

			free(path);
		}
	
		sceIoClose(fp);
	}
}

void getConfigs(Plugins plugins[]){
	SceUID fp;
	bool next = false;
	int lineNB = 512;
	char line[lineNB];
	char *path;
	char *token;

	for (int i = 0; plugins[i].name != '\0'; i++) {
		fp = sceIoOpen(configsPath, SCE_O_RDONLY, 0777);

		if (fp >= 0) {
			next = false;
			while (sceIoRead(fp, line, lineNB) && !next)  {
		    	if (strstr(line, plugins[i].name) != NULL && (token = strtok(line, " ")) != NULL){
	    			path = malloc(sizeof(char) * (strlen(token) + 1));
	    			strcpy(path, token);
    				if ((token = strtok(NULL, " ")) != NULL && strstr(token, "1") != NULL && access(path, F_OK ) != -1){
						next = true;
						plugins[i].active = true;
    				} else plugins[i].active = false;
	    			free(path);
		    	} else plugins[i].active = false;
			}
			sceIoClose(fp);
		}
	}
}