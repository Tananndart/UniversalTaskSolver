#pragma once

#include "Objects.h"

#include <vector>
#include <map>
#include <set>
#include <memory>

class Board;
typedef std::shared_ptr<Board> BoardPtr;

class Board
{
public:	
	Board(const int col_count, const int row_count);

	// add objects
	void add_object(const BaseObjPtr obj);
	void add_object(int col, int row, const BaseObjPtr obj);

	// pop objects
	BaseObjPtr pop_object(int obj_id);

	// delete objects
	void delete_object(int obj_id);
	void delete_all_objects();
	void delete_all_objects(int col, int row);

	// info
	int get_object_count() const;
	int get_object_count(int col, int row) const;
	int get_col_count() const;
	int get_row_count() const;

	// get objects
	BaseObjPtr get_object(int obj_id);

	template <typename OutIt>
	void get_objects(OutIt out_iterator);

	template <typename ObjType, typename OutIt>
	void get_objects(OutIt out_iterator);

	template <typename OutIt>
	void get_objects(int col, int row, OutIt out_iterator);

	template <typename ObjType, typename OutIt>
	void get_objects(int col, int row, OutIt out_iterator);

private:
	struct WrapBaseObject;
	struct Cell;
	typedef std::map<int, WrapBaseObject> ArrayWrapObjects;
	typedef std::vector<std::vector<Cell>> Table;

private:
	ArrayWrapObjects m_wrap_objects;										
	Table m_table;			
	
	const int m_col_count, m_row_count;
};

struct Board::WrapBaseObject
{
	WrapBaseObject() : col(-1), row(-1), obj(nullptr) {}
	WrapBaseObject(int col, int row, BaseObjPtr object) :
		col(col), row(row), obj(object) {}

	BaseObjPtr obj;
	int col, row;
};

struct Board::Cell
{
	Cell() : col(-1), row(-1) {}
	Cell(int col, int row) : col(col), row(row) {}

	std::set<int> objects_ids;
	int col, row;
};

template<typename OutIt>
inline void Board::get_objects(OutIt out_iterator)
{
	for (auto it = m_wrap_objects.begin(); it != m_wrap_objects.end(); ++it)
		*out_iterator++ = it->second.obj;
}

template <typename ObjType, typename OutIt>
inline void Board::get_objects(OutIt out_iterator)
{
	for (auto it = m_wrap_objects.begin(); it != m_wrap_objects.end(); ++it)
	{
		std::shared_ptr<ObjType> obj = std::dynamic_pointer_cast<ObjType>(it->second.obj);
		if (obj)
			*out_iterator++ = obj;
	}
}

template<typename OutIt>
inline void Board::get_objects(int col, int row, OutIt out_iterator)
{
	if (col >= m_col_count || row >= m_row_count)
		return;

	const Cell & cell = m_table[col][row];
	for (auto it = cell.objects_ids.cbegin(); it != cell.objects_ids.cend(); ++it)
	{
		const int obj_id = *it;
		*out_iterator++ = m_wrap_objects[obj_id].obj;
	}
}

template <typename ObjType, typename OutIt>
inline void Board::get_objects(int col, int row, OutIt out_iterator)
{
	if (col >= m_col_count || row >= m_row_count)
		return;

	const Cell & cell = m_table[col][row];
	for (auto it = cell.objects_ids.cbegin(); it != cell.objects_ids.cend(); ++it)
	{
		const int obj_id = *it;
		std::shared_ptr<ObjType> obj = std::dynamic_pointer_cast<ObjType>(m_wrap_objects[obj_id].obj);
		if (obj)
			*out_iterator++ = obj;
	}
}
