#ifndef YAMI_CAMERA_CONFIG_H
#define YAMI_CAMERA_CONFIG_H

#include "../../Maths/Maths.h"

namespace yami
{
	static const float DEFAULT_FOV			= yami::MathsConstatns::PI / 4.0f; // 45 deg
	static const float DEFAULT_ZNEAR		= 0.1f;
	static const float DEFAULT_ZFAR			= 100.0f;

	static const float CAMERA_WIDTH			= 600.0f;
	static const float FPS_CAMERA_SPEED		= 10.0f;
	static const float MOUSE_SENSITIVITY_X	= 100.0f;
	static const float MOUSE_SENSITIVITY_Y	= 100.0f;
}

#endif
