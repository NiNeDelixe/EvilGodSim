#pragma once
#ifndef INTERFACES_IMETACLASS_H_
#define INTERFACES_IMETACLASS_H_

#include "enginecore/core/CoreDefines.h"

class IMetaClass
{
protected:
    IMetaClass() = default;

public:
    virtual ~IMetaClass() = default;

public:
    virtual std::string toString() const { return getType(); }
	const std::string getType() const { return typeid(*this).name(); }

private:
    
};

#endif  // INTERFACES_IMETACLASS_H_
