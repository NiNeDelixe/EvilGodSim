#pragma once
#ifndef ENGINE_COREDEFINES_H_
#define ENGINE_COREDEFINES_H_

#include <memory>

#include <glm/ext.hpp>

#include "enginecore/utils/types/CoreTypesDefines.h"
#include "enginecore/utils/types/FixedPoint.h"

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
    friend class Class##Private;

#define D_PTR(Class) Class##Private * const d = d_func()

#define DECLARE_DPTR(Class) Class##Private d_ptr = std::shared_ptr<Class>

#define DISABLE_COPY(Class) \
    private: Class(const Class &); \
    private: Class &operator=(const Class &);

#define ENGINE_NAMESPACE egengine
#define ENGNMSP ENGINE_NAMESPACE

#define UTILS_NAMESPACE utils
#define UTLSNMSP UTILS_NAMESPACE

#define CORE_NAMESPACE core
#define CRNMSP CORE_NAMESPACE

#define EVENT_NAMESPACE events
#define EVNTNMSP EVENT_NAMESPACE

#define CONCEPTS_NAMESPACE conecepts
#define CNCPTSNMSP CONCEPTS_NAMESPACE

constexpr auto GL_LOG_LEN = 512;
constexpr auto ENGINE_LOGS_DIRECTORY = "logs";

#define DECLARE_PTR(Class) using Ptr = std::shared_ptr<Class>;
#define DECLARE_WPTR(Class) using WeakPtr = std::weak_ptr<Class>;

#define GETTER(type, field, Name) const type& get##Name() const { return this->field; }  
#define SETTER(type, field, Name) void set##Name(const type& value) { this->field = value; } 

#define SSETTER(type, field, Name) void Name(const type& value) { this->field = value; }  
#define SGETTER(type, field, Name) const type& Name() const { return this->field; }  

#define GETTER_VAL(type, field, Name) type get##Name() const { return this->field; }  
#define SH_GETTER_VAL(type, field, Name) type Name() const { return this->field; }  

#define GET_SET_ERS(type, field, Name) GETTER(type, field, Name) SETTER(type, field, Name)
#define SH_GET_SET_ERS(type, field, Name) SGETTER(type, field, Name) SSETTER(type, field, Name)

#define DECLARE_META_FIELD(type, field) type field; public: auto& set_##field(const type& value) { this->field = value; return *this; }

#define DECLARE_FIELD_WITH_PROPERIES(...) GET_MACRO(__VA_ARGS__, OPT_DECLARE_FIELD_WITH_PROPERIES, DEF_FALSE_DECLARE_FIELD_WITH_PROPERIES)(__VA_ARGS__)

#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define DEF_FALSE_DECLARE_FIELD_WITH_PROPERIES(type, field) OPT_DECLARE_FIELD_WITH_PROPERIES(type, field, false)
#define OPT_DECLARE_FIELD_WITH_PROPERIES(type, field, add_memeber_prefix) IMPL_DECLARE_FIELD_WITH_PROPERIES(type, field, add_memeber_prefix)
#define IMPL_DECLARE_FIELD_WITH_PROPERIES(type, field, add_memeber_prefix) IMPL_DECLARE_FIELD_WITH_PROPERIES_##add_memeber_prefix(type, field)
#define IMPL_DECLARE_FIELD_WITH_PROPERIES_true(type, field) type m_##field; public: GET_SET_ERS(type, m_##field, _##field)
#define IMPL_DECLARE_FIELD_WITH_PROPERIES_false(type, field) type field; public: GET_SET_ERS(type, field, _##field)

using fixedpoint_t = float;

namespace glm
{
    using fixvec2 = glm::vec<2, fixedpoint_t, glm::defaultp>;
    using fixvec3 = glm::vec<3, fixedpoint_t, glm::defaultp>;
    using fixvec4 = glm::vec<4, fixedpoint_t, glm::defaultp>;
}


#endif // !ENGINE_COREDEFINES_H_