#pragma once

#ifdef UNIVERSALTASKSOLVER_EXPORTS
#define TASKSOLVER_API __declspec(dllexport) 
#else
#define TASKSOLVER_API __declspec(dllimport) 
#endif

#include <string>
#include <memory>

namespace slv
{
	class IBaseAlg 
	{
	public:
		virtual void print_state(std::ostream& stream) const = 0;

		virtual bool is_win() const = 0;
		virtual bool is_loose() const = 0;

		virtual int get_win_k() const = 0;
		virtual int get_min_win_k() const = 0;
		virtual int get_max_win_k() const = 0;

		virtual void execute_command(int id) = 0;
		virtual int get_command_count() const = 0;
		virtual std::string get_command_name(int id) const = 0;
	};

	class TASKSOLVER_API IGreedyAlg : public IBaseAlg
	{
	public:
		virtual void undo_last_command() = 0;
	};

	class TASKSOLVER_API Solver
	{
	public:
		typedef std::shared_ptr<Solver> Ptr;
	public:
		void execute(std::ostream& stream, std::shared_ptr<IBaseAlg> game_interface);
	};
}