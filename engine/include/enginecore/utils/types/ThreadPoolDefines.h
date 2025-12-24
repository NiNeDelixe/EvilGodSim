#pragma once
#ifndef TYPES_THREADPOOLDEFINES_H_
#define TYPES_THREADPOOLDEFINES_H_

#include <BS_thread_pool.hpp>

using ThreadPool = BS::thread_pool<BS::tp::none>;
#define ENGINE_THREADPOOL_NAMESPACE BS

#endif // !TYPES_THREADPOOLDEFINES_H_