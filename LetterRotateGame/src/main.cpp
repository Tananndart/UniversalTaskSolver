#include <iostream>
#include <string>

#include "LetterRotateGame.h"
#include "UniversalTaskSolver.h"

using namespace std;

char word_1[5] = "3E1D";
char word_2[5] = "L7T3";
char win_word_1[5] = "1E7T";
char win_word_2[5] = "3L3D";



void main()
{
	slv::Solver* solver = new slv::Solver();

	LetRotGame* game = new LetRotGame(word_1, word_2, win_word_1, win_word_2, 100);
	//game->print_state(cout);
	solver->execute(cout, game);
	//cout << game->is_win() << endl;
	/*
	game->rotate_center_counter_clockwise();
	game->print_words(cout);

	game->rotate_left_counter_clockwise();
	game->print_words(cout);

	game->rotate_right_clockwise();
	game->print_words(cout);
	//solver->print(cout, game->is_win);
	//cout << game->is_win();
	*/
	delete game;
	delete solver;

	char ch_stop;
	cin >> ch_stop;
}