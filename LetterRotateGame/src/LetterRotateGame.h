#pragma once

#include <map>

#include "UniversalTaskSolver.h"

class LetRotGame : public slv::ITask
{
public:
	typedef std::shared_ptr<LetRotGame> Ptr;
public:
	static const int WORD_LENGTH = 4;

	// constructor
	LetRotGame(char word_1[WORD_LENGTH + 1], char word_2[WORD_LENGTH + 1],
		char win_word_1[WORD_LENGTH + 1], char win_word_2[WORD_LENGTH + 1],
		unsigned execute_command_max);

	// play game with user
	void play(std::istream& in_stream, std::ostream& out_stream);

	// implementation ITask
	void reset() override;

	bool is_solve() const override;
	bool is_loose() const override;

	int get_solve_k() const override;
	int get_min_solve_k() const override;
	int get_max_solve_k() const override;

	void execute_command(int id) override;
	int get_command_count() const override;
	std::string get_command_name(int id) const override;

	int create_cast() const override;
	void delete_cast(int cast_id) const override;
	void activate_cast(int cast_id) override;

	void print_state(std::ostream& out_stream) const override;

	// commands
	void rotate_left_clockwise();
	void rotate_left_counter_clockwise();
	void rotate_center_clockwise();
	void rotate_center_counter_clockwise();
	void rotate_right_clockwise();
	void rotate_right_counter_clockwise();

private:
	typedef void(LetRotGame::*ptr_command)();
	struct Command
	{
		Command() : name(""), desc(""), body(nullptr) {}
		Command(const std::string& name, const std::string& desc, ptr_command comm)
			: name(name), desc(desc), body(comm) {}
		std::string name, desc;
		ptr_command body;
	};

	struct Cast
	{
		std::string word_1, word_2;
		unsigned execute_comm_cnt;
	};
private:
	std::string m_word_1, m_win_word_1;
	std::string m_word_2, m_win_word_2;
	std::string m_orig_word_1, m_orig_word_2;
	unsigned m_execute_command_max;
	unsigned m_execute_command_cnt;
	std::map<int, Command> m_commands;
	mutable std::map<int, Cast> m_casts;
	mutable int m_cast_id_counter;

	// helpers
	void rotate_clockwise(unsigned st_ch);
	void rotate_counter_clockwise(unsigned st_ch);
};