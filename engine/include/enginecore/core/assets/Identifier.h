#pragma once
#ifndef ASSETS_IDENTIFIER_H_
#define ASSETS_IDENTIFIER_H_

#include "enginecore/core/CoreDefines.h"

class Identifier
{
public:
	Identifier(const std::string& namespace_name, const std::string& asset_name);
	~Identifier() = default;

public:
	GETTER(std::string, m_asset_name, AssetName);
	GETTER(std::string, m_namespace_name, NamespaceName);

	SETTER(std::string, m_asset_name, AssetName);
	SETTER(std::string, m_namespace_name, NamespaceName);

private:
	std::string m_namespace_name;
	std::string m_asset_name;
};

#endif // !ASSETS_IDENTIFIER_H_