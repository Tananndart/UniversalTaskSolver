#include "Board.h"

using namespace std;

Board::Board(const int col_count, const int row_count) :
	m_col_count(col_count), m_row_count(row_count)
{
	auto & cols = m_table;
	cols.resize(col_count);
	for (unsigned col = 0; col < m_table.size(); ++col)
	{
		auto & rows = m_table[col];
		rows.resize(row_count);
		for (unsigned row = 0; row < rows.size(); ++row)
			rows[row] = Cell(col, row);
	}		
}

void Board::add_object(const BaseObjPtr obj)
{
	m_wrap_objects[obj->id()] = WrapBaseObject(-1, -1, obj);
}

void Board::add_object(int col, int row, const BaseObjPtr obj)
{
	Cell & cell = m_table[col][row];
	cell.objects_ids.insert(obj->id());

	m_wrap_objects[obj->id()] = WrapBaseObject(col, row, obj);
}

BaseObjPtr Board::pop_object(int obj_id)
{
	auto obj_it = m_wrap_objects.find(obj_id);
	if (obj_it == m_wrap_objects.end())
		return nullptr;

	WrapBaseObject & wrap_obj = obj_it->second;
	Cell & cell = m_table[wrap_obj.col][wrap_obj.row];

	m_wrap_objects.erase(obj_id);
	cell.objects_ids.erase(obj_id);

	return wrap_obj.obj;
}

void Board::delete_object(int obj_id)
{
	auto it_wrap_obj = m_wrap_objects.find(obj_id);
	if (it_wrap_obj == m_wrap_objects.end())
		return;

	WrapBaseObject & wrap_obj = it_wrap_obj->second;
	const int col = wrap_obj.col;
	const int row = wrap_obj.row;

	if (col >= 0 && row >= 0)
	{
		Cell & cell = m_table[col][row];
		cell.objects_ids.erase(obj_id);
	}
	
	m_wrap_objects.erase(obj_id);
}

void Board::delete_all_objects()
{
	m_wrap_objects.clear();
	
	for (unsigned col = 0; col < m_table.size(); ++col)
		for (unsigned row = 0; row < m_table[col].size(); ++row)
			m_table[col][row].objects_ids.clear();
}

void Board::delete_all_objects(int col, int row)
{
	if (col >= m_col_count || row >= m_row_count)
		return;

	Cell & cell = m_table[col][row];
	for (auto it = cell.objects_ids.begin(); it != cell.objects_ids.end(); ++it)
	{
		const int obj_id = *it;
		m_wrap_objects.erase(obj_id);
	}

	cell.objects_ids.clear();
}

int Board::get_object_count() const
{
	return m_wrap_objects.size();
}

int Board::get_object_count(int col, int row) const
{
	if (col >= m_col_count || row >= m_row_count)
		return -1;

	return m_table[col][row].objects_ids.size();
}

BaseObjPtr Board::get_object(int obj_id)
{
	auto obj_it = m_wrap_objects.find(obj_id);
	return (obj_it == m_wrap_objects.end()) ? nullptr : obj_it->second.obj;
}

int Board::get_col_count() const
{
	return m_col_count;
}

int Board::get_row_count() const
{
	return m_row_count;
}
