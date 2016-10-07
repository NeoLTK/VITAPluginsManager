void controle(SceCtrlData pad, int *navOffset, bool *exit, Plugins plugins[], SceUInt64 *timer) {
	if (timer[0] >= (timer[1] + 100000)) {
		if (pad.buttons & SCE_CTRL_UP) {
			*navOffset -= 1;
		} else if (pad.buttons & SCE_CTRL_DOWN) {
			*navOffset += 1;
		} else if (pad.buttons & SCE_CTRL_CROSS) {
			bool curStat = plugins[*navOffset].active;
			plugins[*navOffset].active = (curStat == true ? false : true);
			putConfigs(plugins);
			dirPlugins(plugins, *navOffset);
		}

		if (pad.buttons & SCE_CTRL_START) {
			*exit = true;
		}

		timer[1] = timer[0];
	}
}