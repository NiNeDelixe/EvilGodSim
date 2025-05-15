#pragma once
#ifndef ENGINE_COREDEFINES_H_
#define ENGINE_COREDEFINES_H_

#include <memory>

#include "enginecore/utils/types/CoreTypesDefines.h"

template <typename T> static inline T* getPtrHelper(T* ptr) { return ptr; }

template <typename T> static inline T* getPtrHelper(const std::shared_ptr<T>& ptr) { return ptr.get(); }
template <typename T> static inline T* getPtrHelper(const std::unique_ptr<T>& ptr) { return ptr.get(); }

#define DECLARE_PRIVATE(Class)\
    inline Class##Private* d_func() {\
        return reinterpret_cast<Class##Private*>(getPtrHelper(d_ptr));\
    }\
    inline const const Class##Private* d_func() const {\
        return reinterpret_cast<const Class##Private*>(getPtrHelper(d_ptr));\
    }\
    friend class Class##Private

#define D_PTR(Class) Class##Private * const d = d_func()

#define DISABLE_COPY(Class) \
    Class(const Class &); \
    Class &operator=(const Class &);

#define UTILS_NAMESPACE utils
#define CORE_NAMESPACE core
#define EVENT_NAMESPACE events
#define CONCEPTS_NAMESPACE conecepts

constexpr auto GL_LOG_LEN = 512;
constexpr auto ENGINE_LOGS_DIRECTORY = "logs";

#define DECLARE_PTR(Class) using Ptr = std::shared_ptr<Class>
#define DECLARE_WPTR(Class) using WeakPtr = std::weak_ptr<Class>

#endif // !ENGINE_COREDEFINES_H_