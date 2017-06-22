#include <iostream>
#include <string>

#include "LetterRotateGame.h"

using namespace std;

char word_1[5] = "3E1D";
char word_2[5] = "L7T3";
char win_word_1[5] = "1E7T";
char win_word_2[5] = "3L3D";

void main()
{
	LetRotGame::Ptr game = make_shared<LetRotGame>(word_1, word_2, win_word_1, win_word_2, 100);	

	//game->play(cin, cout);

	slv::SolverPtr solver = make_shared<slv::Solver>();
	solver->execute(cout, game);

	char ch_stop;
	cin >> ch_stop;
}