#include "AssetManager.h"
#include "Log.h"

#include<iostream>

namespace le { namespace tools {

map<std::string, gfx::Model*> AssetManager::loadedModels;

gfx::Model* AssetManager::LoadModel(std::string _path) 
{
	gfx::Model* toReturn;

	// Try to find the model on the map
	map<std::string, gfx::Model*>::iterator it = loadedModels.find(_path);
	if (it != loadedModels.end())
	{
		toReturn = it->second;
	}
	// If not on the map just load the model
	else 
	{
		toReturn = new gfx::Model(_path);
		loadedModels[_path] = toReturn;
	}
	return toReturn;
}

void AssetManager::Dispose()
{
	for (std::map<std::string, gfx::Model*>::iterator it = loadedModels.begin(); it != loadedModels.end(); ++it)
		delete it->second;
	LOG_CORRECT("Asset Manager Disposed");
}

}}