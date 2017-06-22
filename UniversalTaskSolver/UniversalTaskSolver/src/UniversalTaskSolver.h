#pragma once

#include "Defines.h"

#include <string>
#include <memory>
#include <vector>

namespace slv
{
	class TASKSOLVER_API ITask;
	class TASKSOLVER_API Solver;

	typedef std::shared_ptr<ITask> ITaskPtr;
	typedef std::shared_ptr<Solver> SolverPtr;

	class TASKSOLVER_API ITask
	{
	public:
		virtual void reset() = 0;

		virtual bool is_solve() const = 0;
		virtual bool is_loose() const = 0;

		virtual int get_solve_k() const = 0;
		virtual int get_min_solve_k() const = 0;
		virtual int get_max_solve_k() const = 0;

		virtual void execute_command(int comm_id) = 0;
		virtual int get_command_count() const = 0;
		virtual std::string get_command_name(int comm_id) const = 0;

		virtual int create_cast() const = 0;
		virtual void delete_cast(int cast_id) const = 0;
		virtual void activate_cast(int cast_id) = 0;

		virtual void print_state(std::ostream& out_stream) const = 0;
	};

	class TASKSOLVER_API Solver
	{		
	public:
		void execute(std::ostream& stream, ITaskPtr task_interface);
	};
}