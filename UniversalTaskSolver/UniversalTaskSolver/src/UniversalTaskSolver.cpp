#include "UniversalTaskSolver.h"

namespace slv
{
	using namespace std;

	void Solver::execute(std::ostream& stream, shared_ptr<IBase> game_base)
	{
		auto game = static_pointer_cast<IGreedyAlg>(game_base);
		if (game)
		{
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
		}
	}

}
