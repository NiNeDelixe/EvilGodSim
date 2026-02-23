#pragma once
#ifndef TYPES_THREADPOOLDEFINES_H_
#define TYPES_THREADPOOLDEFINES_H_

#include <tbb/parallel_for.h>
#include <tbb/parallel_for_each.h>
#include <tbb/task_arena.h>
#include <tbb/task_scheduler_observer.h>
//#include <tbb/task_scheduler_init.h>

//using ThreadPool = ;
#define ENGINE_THREADPOOL_NAMESPACE tbb
#define ENGTHRDPL ENGINE_THREADPOOL_NAMESPACE

#endif // !TYPES_THREADPOOLDEFINES_H_