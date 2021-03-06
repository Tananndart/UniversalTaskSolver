#include <iostream>
#include "I_GameView.h"

using namespace std;

void main()
{
	// create model
	IGameModelPtr model = IGameModel::create();

	//config model
	model->create_board(4, 4);
	model->create_ball(1, 1, 1);
	model->create_ball(2, 0, 3);
	model->create_hole(1, 0, 0);
	model->create_hole(2, 3, 2);
	model->create_wall(0, 1, 0, 2);
	model->create_wall(2, 1, 3, 1);
	model->bind_ball_with_hole(1, 1);
	model->bind_ball_with_hole(2, 2);

	// create controller
	IGameControllerPtr controller = IGameController::create(model);

	// create view
	IGameViewPtr view = IGameView::create(model, controller, cout, cin);

	// start game loop
	view->start_game_loop();

	/*
	BallsAndHolesGamePtr game = make_shared<BallsAndHolesGame>();

	game->create_board(4, 4);

	game->create_ball(1, 1, 1);
	game->create_ball(2, 0, 3);

	game->create_hole(1, 0, 0);
	game->create_hole(2, 3, 2);

	game->create_wall(0, 1, 0, 2);
	game->create_wall(2, 1, 3, 1);

	game->bind_ball_with_hole(1, 1);
	game->bind_ball_with_hole(2, 2);

	game->play(cout, cin);
	*/

	/*
	game->draw_board(cout);
	
	game->incline_board_right();
	game->draw_board(cout);

	game->incline_board_left();
	game->draw_board(cout);
	*/
	char ch;
	cin >> ch;
}