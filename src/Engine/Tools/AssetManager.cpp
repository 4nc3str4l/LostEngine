#include "AssetManager.h"
#include "Log.h"

#include<iostream>

namespace le { namespace tools {

map<std::string, std::shared_ptr<gfx::Model>> AssetManager::loadedModels;

std::shared_ptr<gfx::Model> AssetManager::LoadModel(std::string _path) 
{
	std::shared_ptr<gfx::Model> toReturn;

	// Try to find the model on the map
	map<std::string, std::shared_ptr<gfx::Model>>::iterator it = loadedModels.find(_path);
	if (it != loadedModels.end())
	{
		toReturn = it->second;
	}
	// If not on the map just load the model
	else 
	{
		std::shared_ptr<gfx::Model> m(new gfx::Model(_path));
		toReturn = m;
		loadedModels[_path] = m;
	}
	return toReturn;
}

void AssetManager::Dispose()
{
	LOG_CORRECT("Asset Manager Disposed");
}

}}