#include "LetterRotateGame.h"

LetRotGame::LetRotGame(char word_1[WORD_LENGTH + 1], char word_2[WORD_LENGTH + 1], 
	char win_word_1[WORD_LENGTH + 1], char win_word_2[WORD_LENGTH + 1],
	unsigned execute_command_max) 
	: m_word_1(word_1), m_word_2(word_2),
	m_win_word_1(win_word_1), m_win_word_2(win_word_2),
	m_execute_command_max(execute_command_max),
	m_execute_command_cnt(0)
{
	// init commands
	m_commands[0] = Command("rotate_left_clockwise", &LetRotGame::rotate_left_clockwise);
	m_commands[1] = Command("rotate_left_counter_clockwise", &LetRotGame::rotate_left_counter_clockwise);
	m_commands[2] = Command("rotate_center_clockwise", &LetRotGame::rotate_center_clockwise);
	m_commands[3] = Command("rotate_center_counter_clockwise", &LetRotGame::rotate_center_counter_clockwise);
	m_commands[4] = Command("rotate_right_clockwise", &LetRotGame::rotate_right_clockwise);
	m_commands[5] = Command("rotate_right_counter_clockwise", &LetRotGame::rotate_right_counter_clockwise);
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

void LetRotGame::execute_command(int id)
{
	auto it = m_commands.find(id);
	if (it != m_commands.end())
		(this->*it->second.body)();
}

int LetRotGame::get_win_k() const
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

int LetRotGame::get_min_win_k() const
{
	return 0;
}

int LetRotGame::get_max_win_k() const
{
	return WORD_LENGTH * 2;
}

bool LetRotGame::is_win() const
{
	return (m_word_1.compare(m_win_word_1) == 0) &&
		(m_word_2.compare(m_win_word_2) == 0);
}

bool LetRotGame::is_loose() const
{
	return (m_execute_command_cnt > m_execute_command_max);
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
