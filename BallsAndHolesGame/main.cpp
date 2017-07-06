#include <iostream>
#include "BallsAndHolesGame.h"

using namespace std;

void main()
{
	
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