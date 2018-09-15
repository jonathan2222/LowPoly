#ifndef YAMI_MATERIAL_H
#define YAMI_MATERIAL_H

#include "../../Maths/Vectors/Vec4.h"

namespace yami
{
	namespace Material
	{
		struct MaterialData
		{
			yami::Vec4 ambientColor;
			yami::Vec4 diffuseColor;
			yami::Vec4 specularColor;
		};
	}
}

#endif
