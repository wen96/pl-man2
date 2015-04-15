#pragma once

#include <iostream>

namespace masterclient {
	enum LauncherElement {
		BTN_START,
		TAB_CONTROL,

		BTN_FILE_SCRIPT,
		EDT_FILE_SCRIPT,

		LST_BOX_DRIVER,

		CHK_BOX_FULLSCREEN,
		CHK_BOX_MUSIC,
		CHK_BOX_SHADOWS,
		CHK_BOX_ADDITIVE,
		CHK_BOX_VSYNC,
		CHK_BOX_AA,

		EDT_SERVER_HOST,
		EDT_SERVER_PORT,
		CHK_BOX_BLOCK_PIPES,

		COUNT
	};

	const static std::string DRIVER_OPTION = "driver";
	const static std::string FULLSCREEN_OPTION = "fullscreen";
	const static std::string MUSIC_OPTION = "music";
	const static std::string SHADOWS_OPTION = "shadows";
	const static std::string ADDITIVE_OPTION = "additive";
	const static std::string VSYNC_OPTION = "vsync";
	const static std::string AA_OPTION = "aa";
	const static std::string PIPES_OPTION = "pipes";
}
