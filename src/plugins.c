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

char* mStrCapy(char **str, char *mstrcpy, char *mstrcat){
	*str = malloc(sizeof(char) * (strlen(mstrcpy) + strlen(mstrcat) + 1));

	strcpy(*str, mstrcpy);
	strcat(*str, mstrcat);

	return *str;
}

void dirPlugins(Manager *pluginsManager) {
	int offset = pluginsManager->navOffset;
	Plugins *plugins = &(pluginsManager->plugins[offset]);

	char *defPath = mStrCapy(&defPath, defaultPath, plugins->name);
	char *disPath = mStrCapy(&disPath, disablePath, plugins->name);

	if (plugins->active == false){
		if (access(defPath, F_OK ) == -1) {
			rename (disPath, defPath);
			plugins->active = true;

			free(plugins->path);
			plugins->path = (char *) malloc(strlen(defPath) + 1);
			memcpy(plugins->path, defPath, strlen(defPath) + 1);
		} else {
			plugins->active = true;
		}
		
	} else { 
		if (access(defPath, F_OK ) != -1)
			rename (defPath, disPath);

		plugins->active = false;

		free(plugins->path);
		plugins->path = (char *) malloc(strlen(disPath) + 1);
		memcpy(plugins->path, disPath, strlen(disPath) + 1);
	}

	free(disPath);
	free(defPath);
}


void getPlugins (Manager *pluginsManager) {
	struct SceIoDirent item;
	Plugins *plugins = pluginsManager->plugins;
	char *path[2] = {defaultPath, disablePath};
	int fd, offset = 0;
	
	for (int i = 0; i <= 1; i++) {
		if ((fd = sceIoDopen(path[i])) < 0) continue;

		while (sceIoDread(fd, &item)) {
			if (strstr(item.d_name, "suprx") == NULL) continue;

			plugins[offset].name = mStrCapy(&(plugins[offset].name), item.d_name, "");
	    	plugins[offset].path = mStrCapy(&(plugins[offset].path), path[i], item.d_name);
			plugins[offset].pluginsManager = (Manager *) pluginsManager;
	    	plugins[offset].active = false;

			offset++;
		}

	    sceIoDclose(fd);
	}

    plugins[offset].name = malloc(sizeof(char));
   	plugins[offset].name = '\0';
}

void enablePlugins(Plugins *plugins){
	if (!plugins->active){
		dirPlugins(plugins->pluginsManager);
		putConfigs(plugins->pluginsManager->plugins);
	}
}

void disablePlugins(Plugins *plugins){
	if (plugins->active){
		dirPlugins(plugins->pluginsManager);
		putConfigs(plugins->pluginsManager->plugins);
	}
}