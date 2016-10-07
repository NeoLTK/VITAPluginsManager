/*
 * 
 * Made by NeoLTK
 * 
 */

#include "header.h"

void dirPlugins(Plugins plugins[], int offset) {
	char *tmp = malloc(sizeof(char) * (strlen(disablePath) + strlen(plugins[offset].name)));

	strcpy(tmp, disablePath);
	strcat(tmp, plugins[offset].name);

	if (plugins[offset].active == true){
		if (access(plugins[offset].path, F_OK ) == -1) {
			rename (tmp, plugins[offset].path);
		}
	} else { 
		if (access(plugins[offset].path, F_OK ) != -1) {
			rename (plugins[offset].path, tmp);
		}
	}

	free(tmp);
}

int putPlugins(Plugins plugins[], SceIoDirent item, int offset){
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
	path[0] = defaultPath;
	path[1] = disablePath;
	

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