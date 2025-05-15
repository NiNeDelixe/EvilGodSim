#pragma once
#ifndef LOADERS_AUTOREGISTERLOADER_H_
#define LOADERS_AUTOREGISTERLOADER_H_

#include <memory>

#include <glog/logging.h>

#include "enginecore/core/assets/AssetsLoader.h"

template<AssetType tag, /*CONCEPTS_NAMESPACE::IsDerivedFromIAssetLoader*/class LOADER>
class AutoRegisterLoader 
{
protected:
    static bool registerLoader() 
    {
		try
		{
			AssetsLoader::instance()->addLoader(tag, std::make_shared<LOADER>(AssetsManager::instance().get()));
		}
		catch (const std::exception& exc)
		{
			LOG(ERROR) << "Failed to register loader: " << typeid(LOADER).name() << "\n\tbecause: " << exc.what();
			return false;
		}
        
        return true;
    }

    static inline bool m_registered = registerLoader();
};

#endif // !LOADERS_AUTOREGISTERLOADER_H_