/* Author: Tananndart */
#pragma once

#include <memory>
#include <list>
#include <map>
#include <algorithm>

namespace grp
{
	class Graph
	{
	public:
		//typedef std::shared_ptr<T> DataPtr;
		typedef int DataPtr;
	public:
		Graph();

		// node create
		int create_node(const DataPtr data);

		// node delete
		void delete_node(int node_id);
		void delete_all_nodes();
		void delete_node_all_links(int node_id);

		// node set
		void set_node_data(int node_id, const DataPtr data);

		// node get
		DataPtr get_node_data(int node_id);
		unsigned get_node_count();
		unsigned get_node_link_count(int node_id);
		template <class IT> void get_all_node_id(IT begin);

		/*
		template <class IT> void get_node_all_neighbor_id(IT begin, IT end);
		template <class IT> void get_node_all_link_id(IT begin, IT end);

		// link create
		int create_link(int node_id_1, int node_id_2, int weight);

		// link delete
		void delete_link(int link_id);
		void delete_link(int node_id_1, int node_id_2);
		void delete_all_links();

		// link set
		void set_link_weight(int link_id, int weight);

		// link get
		int get_link_count();
		int get_link_id(int node_id_1, int node_id_2);
		int get_link_weight(int link_id);
		int get_link_weight(int node_id_1, int node_id_2);
		template <class IT> void get_all_link_id(IT begin, IT end);

		// link exist
		bool exist_link(int node_id_1, int node_id_2);
		*/
			
	private:
		struct Link;

		struct Node
		{
			int id;
			DataPtr data;
			std::list<std::shared_ptr<Link>> links;
		};

		struct Link
		{
			int id;
			int weight;
			std::weak_ptr<Node> first_node, second_node;
		};

	private:
		int m_id_counter;
		std::map<int, std::shared_ptr<Node>> m_nodes;
		std::map<int, std::shared_ptr<Node>> m_links;

		int get_new_id();
	};


	template<class IT>
	inline void Graph::get_all_node_id(IT begin)
	{
		for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
		{
			*begin = it->first;
			++begin;
		}
	}

}