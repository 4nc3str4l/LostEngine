#pragma once

#include<map>
#include<string>
#include "../Gfx/Models/Model.h"
#include <memory>

namespace le { namespace tools {

	class AssetManager
	{
	public:
		static std::map <std::string, std::shared_ptr<gfx::Model>> loadedModels;
		static std::shared_ptr<gfx::Model> LoadModel(std::string _path);
		static void Dispose();
	};
}}
