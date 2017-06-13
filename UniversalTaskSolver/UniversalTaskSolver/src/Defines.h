#pragma once

#ifdef UNIVERSALTASKSOLVER_EXPORTS
#define TASKSOLVER_API __declspec(dllexport) 
#else
#define TASKSOLVER_API __declspec(dllimport) 
#endif

// from use test
#define UNIVERSALTASKSOLVER_TESTS

#ifdef UNIVERSALTASKSOLVER_TESTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API
#endif