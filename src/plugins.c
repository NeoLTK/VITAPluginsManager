/*
 * 
 * Made by NeoLTK
 * 
 */

#include "header.h"


int find(char *fileName, char *strSearch) {
	FILE *f;
	char c;
	int found = 0;
	int pos = 0;
	int length;

	f = fopen(fileName,"r");
	if (f == NULL)
		return 0;

	length = strlen(strSearch);

	while (fread(&c, 1, 1, f) > 0 && !found) {

		if (c == strSearch[pos]) {
	  		pos++;
		} else {
	  		if (pos != 0) {
		    	fseek(f, -pos, SEEK_CUR);
		    	pos = 0;
		  	}
		}

		found = (pos == length);

	}

	fclose(f);
	return found;
}



// int searchF(char *path, char **str){
// 	SceUID fp = sceIoOpen(path, SCE_O_RDONLY, 0777);
// 	int size = 1024;
// 	char data[size];

// 	while ((sceIoRead(fp, data, sizeof(data))) > 0){
// 		for (int i = 0; i != 8; i++) {
// 			if(strstr(data, str[i]) != NULL) {
// 				sceIoClose(fp);
// 				return 1;
// 			}
// 		}
// 	}

// 	sceIoClose(fp);
// 	return 0;
// }

void securityCheck(Plugins *plugins){
	char *search[8] = {"savedata0:", "vs0:", "vd0:", "ur0:", "sa0:", "pd0:", "os0:", "ud0:" };

	for (int i = 0; i != 8; i++) {
		if (find(plugins->path, search[i]) == 1) {
			plugins->safe = false;
			return;
		}
	}
	
	plugins->safe = true;
	return;
}


void dirPlugins(Manager *pluginsManager) {
	int offset = pluginsManager->navOffset;
	char *defPath = malloc(sizeof(char) * (strlen(defaultPath) + strlen(pluginsManager->plugins[offset].name) + 1));
	char *disPath = malloc(sizeof(char) * (strlen(disablePath) + strlen(pluginsManager->plugins[offset].name) + 1));

	strcpy(disPath, disablePath);
	strcat(disPath, pluginsManager->plugins[offset].name);

	strcpy(defPath, defaultPath);
	strcat(defPath, pluginsManager->plugins[offset].name);	

	if (pluginsManager->plugins[offset].active == false){
		if (access(defPath, F_OK ) == -1 ) {
			rename (disPath, defPath);
			pluginsManager->plugins[offset].active = true;

			free(pluginsManager->plugins[offset].path);
			pluginsManager->plugins[offset].path = (char *) malloc(strlen(defPath) + 1);
			memcpy(pluginsManager->plugins[offset].path, defPath, strlen(defPath) + 1);
		} else {
			pluginsManager->plugins[offset].active = true;
		}
		
	} else { 
		if (access(defPath, F_OK ) != -1) {
			rename (defPath, disPath);
		}

		pluginsManager->plugins[offset].active = false;

		free(pluginsManager->plugins[offset].path);
		pluginsManager->plugins[offset].path = (char *) malloc(strlen(disPath) + 1);
		memcpy(pluginsManager->plugins[offset].path, disPath, strlen(disPath) + 1);
	}

	free(disPath);
	free(defPath);
}

int putPlugins(Plugins plugins[], SceIoDirent item, int offset, char *path){
	if (strstr(item.d_name, "suprx") != NULL) {
    	plugins[offset].name = malloc(sizeof(char) * (strlen(item.d_name) + 1));
    	strcpy(plugins[offset].name, item.d_name);

    	plugins[offset].path = malloc(sizeof(char) * (strlen(path) + strlen(plugins[offset].name) + 1));
    	strcpy(plugins[offset].path, path);
    	strcat(plugins[offset].path, plugins[offset].name);

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
	path[0] = defaultPath;
	path[1] = disablePath;
	

	for (int i = 0; i <= 1; i++) {
		fd = sceIoDopen(path[i]);
		if (fd >= 0) {
			while(sceIoDread(fd, &dir)) 
        		offset = offset + putPlugins(plugins, dir, offset, path[i]);

		    sceIoDclose(fd);
		}
		
	    plugins[offset].name = malloc(sizeof(char));
	   	plugins[offset].name = '\0';
	}
}
