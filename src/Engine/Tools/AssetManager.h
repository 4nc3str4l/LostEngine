#pragma once
#include<map>
#include<string>
#include "../Gfx/Models/Model.h"

namespace le { namespace tools {

	class AssetManager
	{
	public:
		static std::map <std::string, gfx::Model*> loadedModels;
		static gfx::Model* LoadModel(std::string _path);
		static void Dispose();
	};
}}
