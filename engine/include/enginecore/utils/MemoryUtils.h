#pragma once
#ifndef UTILS_MEMORYUTILS_H_
#define UTILS_MEMORYUTILS_H_

#include <memory>

#include "enginecore/core/CoreDefines.h"

namespace UTILS_NAMESPACE
{
	namespace memory
	{
#if !defined(_HAS_CXX20)
		template <class TYPE>
		_NODISCARD_SMART_PTR_ALLOC std::shared_ptr<TYPE[]> make_shared(const size_t _Size) { // make a shared_ptr to array object
			std::shared_ptr<TYPE[]> ret = std::shared_ptr<TYPE[]>(new TYPE[_Size]);
			return ret;
		}
#endif
	}
}


#endif // !UTILS_MEMORYUTILS_H_