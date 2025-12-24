#include "enginecore/core/assets/Identifier.h"

Identifier::Identifier(const std::string& m_namespace_name, const std::string& asset_name)
	: m_namespace_name(m_namespace_name), m_asset_name(asset_name)
{
}
