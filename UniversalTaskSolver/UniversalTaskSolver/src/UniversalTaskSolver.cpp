#include "UniversalTaskSolver.h"
#include "GreedyAlg.h"

namespace slv
{
	using namespace std;

	void Solver::execute(std::ostream& stream, ITaskPtr task)
	{
		if (task)
		{
			// create TaskGraph
			TaskGraphPtr graph = make_shared<TaskGraph>();
			if (!graph->init(task))
				return;

			// create greedy alg
			GreedyAlgPtr greedy_alg = make_shared<GreedyAlg>();

			// execute greedy alg
			const int MAX_EXECUTE_COMMANDS = 100;
			vector<int> res_commands;
			if (greedy_alg->execute(graph, res_commands, MAX_EXECUTE_COMMANDS, &stream))
				stream << "IS SOLVE!!!" << endl;
			else stream << "EPIC FAIL!" << endl;

			for (unsigned i = 0; i < res_commands.size(); ++i)
				stream << task->get_command_name(res_commands[i]) << endl;
			

			/*
			// solve game for test
			game->print_state(stream);
			stream << game->is_win() << endl;

			stream << game->get_win_k() << endl;

			game->execute_command(3); //rotate_center_counter_clockwise
			game->print_state(stream);
			stream << game->get_win_k() << endl;

			game->execute_command(1); //rotate_left_counter_clockwise
			game->print_state(stream);
			stream << game->get_win_k() << endl;

			game->execute_command(4); //rotate_right_clockwise	
			game->print_state(stream);
			stream << game->get_win_k() << endl;

			stream << game->is_win();
			stream << game->get_win_k() << endl;
			*/
		}
	}

}
