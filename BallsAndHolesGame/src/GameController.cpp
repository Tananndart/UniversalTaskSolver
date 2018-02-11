#include "GameController.h"

#include <string>

using namespace std;

GameController::GameController(IGameModelPtr model)
	: m_model(model)
{}	

bool GameController::handle_input_command(const string & command_str)
{
	// while all commands 1 char
	if (command_str.length() > 1)
		return false;

	if (command_str.compare("W") == 0)
		m_model->incline_board_up();

	if (command_str.compare("S") == 0)
		m_model->incline_board_down();

	if (command_str.compare("A") == 0)
		m_model->incline_board_left();

	if (command_str.compare("D") == 0)
		m_model->incline_board_right();

	return true;
}