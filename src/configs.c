void putConfigs (Plugins plugins[]){
	FILE* fp = fopen(configsPath, "w");

	if (fp != NULL){
		for (int i = 0; plugins[i].name != '\0'; i++) {
			if (plugins[i].active)
				fprintf(fp, "%s %d\n", plugins[i].path, (plugins[i].active ? 1 : 0));
		}

		fclose(fp);
	}
}

void getConfigs(Plugins plugins[]){
	FILE* fp;
	bool next = false;
	const size_t lineNB = 50;
	char* line = malloc(lineNB);

	for (int i = 0; plugins[i].name != '\0'; i++) {
		fp = fopen(configsPath, "r");

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