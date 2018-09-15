#ifndef YAMI_MODEL_LOADER_H
#define YAMI_MODEL_LOADER_H

#include <string>
#include <vector>
#include "../Core/Scene/Model.h"

namespace yami
{
	class ModelLoader
	{
	public:
		ModelLoader();
		~ModelLoader();

		static Model* loadModel(const std::string& pathName);

	private:

	};
}

#endif
