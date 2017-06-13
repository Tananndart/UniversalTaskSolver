/* Author: Tananndart */
#pragma once

#include "Defines.h"

#include <memory>
#include <list>
#include <map>
#include <algorithm>

namespace grp
{
	struct TEST_API Link;
	struct TEST_API Node;
	class TEST_API Graph;

	typedef std::shared_ptr<Link> LinkPtr;
	typedef std::shared_ptr<Node> NodePtr;
	typedef std::shared_ptr<Graph> GraphPtr;
	
	class TEST_API Graph
	{
	public:
		Graph();

		// create
		NodePtr create_node(const int data);
		LinkPtr create_link();
		LinkPtr create_link(const NodePtr first_node,
			const NodePtr second_node, int weight);
		LinkPtr create_link(int first_node_id, int second_node_id, int weight);

		// reset
		void reset();

		// delete
		bool delete_node(int node_id);
		void delete_all_nodes();
		bool delete_link(int link_id);
		void delete_all_links();

		// exist
		bool exist_node(int node_id) const;
		bool exist_node(const NodePtr node) const;
		bool exist_link(int link_id) const;
		bool exist_link(const LinkPtr link) const;

		// get count
		unsigned get_node_count() const;
		unsigned get_link_count() const;

		// get objects
		NodePtr get_node(int node_id);
		const NodePtr get_node(int node_id) const;
		LinkPtr get_link(int link_id);
		const LinkPtr get_link(int link_id) const;

		// container.resize(get_node_count()); get_all_node_id(cont.begin()); 
		//or use back_inserter: get_all_node_id(back_inserter(cont));
		template <class OutIt> void get_all_nodes_id(OutIt out_it);
		template <class OutIt> void get_all_nodes_ptr(OutIt out_it);
		template <class OutIt> void get_all_link_id(OutIt out_it);
		template <class OutIt> void get_all_link_ptr(OutIt out_it);

	private:
		int m_node_id_counter, m_link_id_counter;
		std::map<int, NodePtr> m_nodes;
		std::map<int, LinkPtr> m_links;

		int get_new_node_id();
		int get_new_link_id();

		Graph(const Graph&) = delete;
		void operator= (const Graph&) = delete;
	};


	struct TEST_API Node
	{
	public:
		typedef std::list<std::shared_ptr<Link>> Links;
	public:
		Node() : m_id(-1), m_data(-1) {}
		Node(const int id) : m_id(id), m_data(-1) {}

		int id() const;

		int get_data() const;
		void set_data(int data);

		Links& get_links();
		const Links& get_links() const;

	private:
		int m_id;
		int m_data;
		Links m_links;
	};

	struct TEST_API Link
	{
	public:
		Link() : m_id(-1), m_weight(0) {}
		Link(const int id) : m_id(id), m_weight(0) {}

		int id() const;

		int get_weight() const;
		void set_weight(int weight);

		std::pair<NodePtr, NodePtr> get_nodes() const;
		void set_nodes(std::pair<NodePtr, NodePtr> nodes);

		NodePtr get_first_node() const;
		void set_first_node(NodePtr node);

		NodePtr get_second_node() const;
		void set_second_node(NodePtr node);		

	private:
		int m_id;
		int m_weight;
		std::weak_ptr<Node> m_first_node, m_second_node;
	};


	template<class OutIt>
	inline void Graph::get_all_nodes_id(OutIt out_it)
	{
		for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
			*out_it++ = it->first;
	}

	template<class OutIt>
	inline void Graph::get_all_nodes_ptr(OutIt out_it)
	{
		for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
			*out_it++ = it->second;
	}

	template<class OutIt>
	inline void Graph::get_all_link_id(OutIt out_it)
	{
		for (auto it = m_links.begin(); it != m_links.end(); ++it)
			*out_it++ = it->first;
	}

	template<class OutIt>
	inline void Graph::get_all_link_ptr(OutIt out_it)
	{
		for (auto it = m_links.begin(); it != m_links.end(); ++it)
			*out_it++ = it->second;
	}
}