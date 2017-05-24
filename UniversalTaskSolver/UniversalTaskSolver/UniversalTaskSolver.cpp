#include "UniversalTaskSolver.h"

void slv::Solver::execute(std::ostream& stream, ITask* game)
{
	game->print_state(stream);
	stream << game->is_win() << std::endl;
	
	game->execute_command(3); //rotate_center_counter_clockwise
	game->print_state(stream);

	game->execute_command(1); //rotate_left_counter_clockwise
	game->print_state(stream);

	game->execute_command(4); //rotate_right_clockwise	
	game->print_state(stream);

	stream << game->is_win();
}
