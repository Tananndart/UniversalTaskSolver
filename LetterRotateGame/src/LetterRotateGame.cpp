#include "LetterRotateGame.h"

using namespace std;

LetRotGame::LetRotGame(char word_1[WORD_LENGTH + 1], char word_2[WORD_LENGTH + 1], 
	char win_word_1[WORD_LENGTH + 1], char win_word_2[WORD_LENGTH + 1], unsigned execute_command_max) 
	: m_word_1(word_1), m_word_2(word_2),
	m_orig_word_1(word_1), m_orig_word_2(word_2),
	m_win_word_1(win_word_1), m_win_word_2(win_word_2),
	m_execute_command_max(execute_command_max),
	m_execute_command_cnt(0),
	m_cast_id_counter(0)
{
	// init commands
	m_commands[0] = Command("+L", "rotate_left_clockwise", &LetRotGame::rotate_left_clockwise);
	m_commands[1] = Command("-L", "rotate_left_counter_clockwise", &LetRotGame::rotate_left_counter_clockwise);
	m_commands[2] = Command("+C", "rotate_center_clockwise", &LetRotGame::rotate_center_clockwise);
	m_commands[3] = Command("-C", "rotate_center_counter_clockwise", &LetRotGame::rotate_center_counter_clockwise);
	m_commands[4] = Command("+R", "rotate_right_clockwise", &LetRotGame::rotate_right_clockwise);
	m_commands[5] = Command("-R", "rotate_right_counter_clockwise", &LetRotGame::rotate_right_counter_clockwise);
}

void LetRotGame::play(istream& in_stream, ostream& out_stream)
{
	out_stream << "Let's go!" << endl;
	out_stream << "This words:" << endl;
	out_stream << m_word_1 << endl << m_word_2 << endl;
	out_stream << "... must be:" << endl;
	out_stream << m_win_word_1 << endl << m_win_word_2 << endl;
	out_stream << endl;

	out_stream << "Your commands:" << endl;
	for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
	{
		const Command& comm = it->second;
		out_stream << comm.name << " - " << comm.desc << endl;
	}
	out_stream << "rs - reset game" << endl;
	out_stream << endl;

	out_stream << "Are you ready? Go!" << endl;
	string str;
	while (!is_solve() || is_loose())
	{
		// TODO: add user input validation
		in_stream >> str;

		if (str.compare("rs") == 0)
		{
			reset();
			out_stream << "reset" << endl;
			print_state(out_stream);
			continue;
		}

		// OPT: bad map use =(
		for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
		{
			const Command& comm = it->second;
			if (comm.name.compare(str) == 0)
			{
				execute_command(it->first);
				out_stream << "Win_K = " << get_solve_k() << endl;
				out_stream << endl;
				print_state(out_stream);
				break;
			}
		}
	}

	if (is_solve())
		out_stream << "WIN!!!" << endl;
	else
		out_stream << "LOOSE!" << endl;

}

void LetRotGame::print_state(std::ostream & stream) const
{
	stream << m_word_1 << " = " << m_win_word_1 << std::endl;
	stream << m_word_2 << " = " << m_win_word_2 << std::endl;
}

int LetRotGame::get_command_count() const
{
	return m_commands.size();
}

std::string LetRotGame::get_command_name(int id) const
{
	auto it = m_commands.find(id);
	if (it != m_commands.end())
		return it->second.name;

	return std::string();
}

int LetRotGame::create_cast() const
{
	int new_id = m_cast_id_counter++;

	Cast new_cast;
	new_cast.word_1 = m_word_1;
	new_cast.word_2 = m_word_2;
	new_cast.execute_comm_cnt = m_execute_command_cnt;

	m_casts[new_id] = new_cast;
	return new_id;
}

void LetRotGame::delete_cast(int cast_id) const
{
	m_casts.erase(cast_id);
}

void LetRotGame::activate_cast(int cast_id)
{
	auto it = m_casts.find(cast_id);
	if (it != m_casts.end())
	{
		const Cast& cast = it->second;
		m_word_1 = cast.word_1;
		m_word_2 = cast.word_2;
		m_execute_command_cnt = cast.execute_comm_cnt;
	}
}

void LetRotGame::execute_command(int id)
{
	auto it = m_commands.find(id);
	if (it != m_commands.end())
		(this->*it->second.body)();
}

int LetRotGame::get_solve_k() const
{
	int res = 0;
	for (int i = 0; i < WORD_LENGTH; ++i)
	{
		if (m_word_1[i] == m_win_word_1[i])
			++res;
		if (m_word_2[i] == m_win_word_2[i])
			++res;
	}
	return res;
}

int LetRotGame::get_min_solve_k() const
{
	return 0;
}

int LetRotGame::get_max_solve_k() const
{
	return WORD_LENGTH * 2;
}

bool LetRotGame::is_solve() const
{
	return (m_word_1.compare(m_win_word_1) == 0) &&
		(m_word_2.compare(m_win_word_2) == 0);
}

bool LetRotGame::is_loose() const
{
	return (m_execute_command_cnt > m_execute_command_max);
}

void LetRotGame::reset()
{
	m_word_1 = m_orig_word_1;
	m_word_2 = m_orig_word_2;
	m_execute_command_cnt = 0;
	m_casts.clear();
	m_cast_id_counter = 0;
}

void LetRotGame::rotate_left_clockwise()
{
	rotate_clockwise(0);
	m_execute_command_cnt++;
}

void LetRotGame::rotate_left_counter_clockwise()
{
	rotate_counter_clockwise(0);
	m_execute_command_cnt++;
}

void LetRotGame::rotate_center_clockwise()
{
	rotate_clockwise(1);
	m_execute_command_cnt++;
}

void LetRotGame::rotate_center_counter_clockwise()
{
	rotate_counter_clockwise(1);
	m_execute_command_cnt++;
}

void LetRotGame::rotate_right_clockwise()
{
	rotate_clockwise(2);
	m_execute_command_cnt++;
}

void LetRotGame::rotate_right_counter_clockwise()
{
	rotate_counter_clockwise(2);
	m_execute_command_cnt++;
}

void LetRotGame::rotate_clockwise(unsigned st_ch)
{
	unsigned fn_ch = st_ch + 1;

	char ch = m_word_1[st_ch];
	m_word_1[st_ch] = m_word_2[st_ch];

	char ch_2 = m_word_1[fn_ch];
	m_word_1[fn_ch] = ch;

	ch = m_word_2[fn_ch];
	m_word_2[fn_ch] = ch_2;

	m_word_2[st_ch] = ch;
}

void LetRotGame::rotate_counter_clockwise(unsigned st_ch)
{
	unsigned fn_ch = st_ch + 1;

	char ch = m_word_2[fn_ch];
	m_word_2[fn_ch] = m_word_2[st_ch];

	char ch_2 = m_word_1[fn_ch];
	m_word_1[fn_ch] = ch;

	ch = m_word_1[st_ch];
	m_word_1[st_ch] = ch_2;

	m_word_2[st_ch] = ch;
}
