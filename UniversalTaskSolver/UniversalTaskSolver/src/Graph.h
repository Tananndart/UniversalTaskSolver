/* Author: Tananndart */
#pragma once

#include "Defines.h"

#include <memory>
#include <list>
#include <map>
#include <algorithm>

namespace grp
{
	template <typename T> struct TEST_API Link;
	template <typename T> struct TEST_API Node;
	template <typename T> class TEST_API Graph;

	//typedef std::shared_ptr<Link<T>> LinkPtr;
	template <typename T>
	using LinkPtr = std::shared_ptr<Link<T>>;

	//typedef std::shared_ptr<Node> NodePtr;
	template <typename T>
	using NodePtr = std::shared_ptr<Node<T>>;

	//typedef std::shared_ptr<Graph<T>> GraphPtr;
	template <typename T>
	using GraphPtr = std::shared_ptr<Graph<T>>;


	template <typename T> class TEST_API Graph
	{
	public:
		Graph<T>();

		// create
		NodePtr<T> create_node(const T& data);
		LinkPtr<T> create_link();
		LinkPtr<T> create_link(const NodePtr<T> first_node,
			const NodePtr<T> second_node, int weight);
		LinkPtr<T> create_link(int first_node_id, int second_node_id, int weight);

		// reset
		void reset();

		// delete
		bool delete_node(int node_id);
		void delete_all_nodes();
		bool delete_link(int link_id);
		void delete_all_links();

		// exist
		bool exist_node(int node_id) const;
		bool exist_node(const NodePtr<T> node) const;
		bool exist_link(int link_id) const;
		bool exist_link(const LinkPtr<T> link) const;

		// get count
		unsigned get_node_count() const;
		unsigned get_link_count() const;

		// get objects
		NodePtr<T> get_node(int node_id);
		const NodePtr<T> get_node(int node_id) const;
		LinkPtr<T> get_link(int link_id);
		const LinkPtr<T> get_link(int link_id) const;

		// container.resize(get_node_count()); get_all_node_id(cont.begin()); 
		//or use back_inserter: get_all_node_id(back_inserter(cont));
		template <class OutIt> void get_all_nodes_id(OutIt out_it);
		template <class OutIt> void get_all_nodes_ptr(OutIt out_it);
		template <class OutIt> void get_all_link_id(OutIt out_it);
		template <class OutIt> void get_all_link_ptr(OutIt out_it);

	private:
		int m_node_id_counter, m_link_id_counter;
		std::map<int, NodePtr<T>> m_nodes;
		std::map<int, LinkPtr<T>> m_links;

		int get_new_node_id();
		int get_new_link_id();

		Graph<T>(const Graph<T>&) = delete;
		void operator= (const Graph<T>&) = delete;
	};

	template <typename T> struct TEST_API Node
	{
	public:
		//typedef std::list<std::shared_ptr<Link<T>>> Links;
		template <typename T>
		using Links = std::list<std::shared_ptr<Link<T>>>;
	public:
		Node<T>() : m_id(-1) {}
		Node<T>(const int id) : m_id(id) {}

		int id() const;

		T get_data() const;
		void set_data(const T& data);

		Links<T>& get_links();
		const Links<T>& get_links() const;

	private:
		int m_id;
		T m_data;
		Links<T> m_links;
	};

	template <typename T> struct TEST_API Link
	{
	public:
		Link<T>() : m_id(-1), m_weight(0) {}
		Link<T>(const int id) : m_id(id), m_weight(0) {}

		int id() const;

		int get_weight() const;
		void set_weight(int weight);

		std::pair<NodePtr<T>, NodePtr<T>> get_nodes() const;
		void set_nodes(std::pair<NodePtr<T>, NodePtr<T>> nodes);

		NodePtr<T> get_first_node() const;
		void set_first_node(NodePtr<T> node);

		NodePtr<T> get_second_node() const;
		void set_second_node(NodePtr<T> node);		

	private:
		int m_id;
		int m_weight;
		std::weak_ptr<Node<T>> m_first_node, m_second_node;
	};

	/////////////////////// Graph //////////////////////////

	template<typename T>
	Graph<T>::Graph() : m_node_id_counter(0), m_link_id_counter(0)
	{}

	template<typename T>
	NodePtr<T> Graph<T>::create_node(const T& data)
	{
		NodePtr<T> node = std::make_shared<Node<T>>(get_new_node_id());
		node->set_data(data);

		m_nodes[node->id()] = node;
		return node;
	}

	template<typename T>
	LinkPtr<T> Graph<T>::create_link()
	{
		LinkPtr<T> link = std::make_shared<Link<T>>(get_new_link_id());
		m_links[link->id()] = link;
		return link;
	}

	template<typename T>
	LinkPtr<T> Graph<T>::create_link(const NodePtr<T> first_node, const NodePtr<T> second_node, int weight)
	{
		if (m_nodes.find(first_node->id()) == m_nodes.end() ||
			m_nodes.find(second_node->id()) == m_nodes.end())
			return nullptr;

		LinkPtr<T> link = std::make_shared<Link<T>>(get_new_link_id());
		link->set_weight(weight);
		link->set_first_node(first_node);
		link->set_second_node(second_node);

		m_links[link->id()] = link;
		return link;
	}

	template<typename T>
	LinkPtr<T> Graph<T>::create_link(int first_node_id, int second_node_id, int weight)
	{
		NodePtr<T> first_node = nullptr;
		auto first_it = m_nodes.find(first_node_id);
		if (first_it != m_nodes.end())
			first_node = first_it->second;

		NodePtr<T> second_node = nullptr;
		auto second_it = m_nodes.find(second_node_id);
		if (second_it != m_nodes.end())
			second_node = second_it->second;

		LinkPtr<T> link = std::make_shared<Link<T>>(get_new_link_id());
		link->set_weight(weight);
		link->set_first_node(first_node);
		link->set_second_node(second_node);

		m_links[link->id()] = link;
		return link;
	}

	template<typename T>
	void Graph<T>::reset()
	{
		m_nodes.clear();
		m_links.clear();
		m_link_id_counter = 0;
		m_node_id_counter = 0;
	}

	template<typename T>
	bool Graph<T>::delete_node(int node_id)
	{
		auto it = m_nodes.find(node_id);
		if (it != m_nodes.end())
		{
			m_nodes.erase(it);
			return true;
		}

		return false;
	}

	template<typename T>
	void Graph<T>::delete_all_nodes()
	{
		m_nodes.clear();
	}

	template<typename T>
	bool Graph<T>::delete_link(int link_id)
	{
		auto it = m_links.find(link_id);
		if (it != m_links.end())
		{
			m_links.erase(it);
			return true;
		}

		return false;
	}

	template<typename T>
	void Graph<T>::delete_all_links()
	{
		m_links.clear();
	}

	template<typename T>
	bool Graph<T>::exist_node(int node_id) const
	{
		return m_nodes.find(node_id) != m_nodes.end();
	}

	template<typename T>
	bool Graph<T>::exist_node(const NodePtr<T> node) const
	{
		if (node == nullptr)
			return false;

		return m_nodes.find(node->id()) != m_nodes.end();
	}

	template<typename T>
	bool Graph<T>::exist_link(int link_id) const
	{
		return m_links.find(link_id) != m_links.end();
	}

	template<typename T>
	bool Graph<T>::exist_link(const LinkPtr<T> link) const
	{
		if (link == nullptr)
			return false;

		return m_links.find(link->id()) != m_links.end();
	}

	template<typename T>
	unsigned Graph<T>::get_node_count() const
	{
		return m_nodes.size();
	}

	template<typename T>
	unsigned Graph<T>::get_link_count() const
	{
		return m_links.size();
	}

	template<typename T>
	NodePtr<T> Graph<T>::get_node(int node_id)
	{
		auto it = m_nodes.find(node_id);
		if (it != m_nodes.end())
			return it->second;

		return nullptr;
	}

	template<typename T>
	const NodePtr<T> Graph<T>::get_node(int node_id) const
	{
		auto it = m_nodes.find(node_id);
		if (it != m_nodes.end())
			return it->second;

		return nullptr;
	}

	template<typename T>
	LinkPtr<T> Graph<T>::get_link(int link_id)
	{
		auto it = m_links.find(link_id);
		if (it != m_links.end())
			return it->second;

		return nullptr;
	}

	template<typename T>
	const LinkPtr<T> Graph<T>::get_link(int link_id) const
	{
		auto it = m_links.find(link_id);
		if (it != m_links.end())
			return it->second;

		return nullptr;
	}

	template<typename T>
	int Graph<T>::get_new_node_id()
	{
		return m_node_id_counter++;
	}

	template<typename T>
	int Graph<T>::get_new_link_id()
	{
		return m_link_id_counter++;
	}

	template<typename T>
	template<class OutIt>
	inline void Graph<T>::get_all_nodes_id(OutIt out_it)
	{
		for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
			*out_it++ = it->first;
	}

	template<typename T>
	template<class OutIt>
	inline void Graph<T>::get_all_nodes_ptr(OutIt out_it)
	{
		for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
			*out_it++ = it->second;
	}

	template<typename T>
	template<class OutIt>
	inline void Graph<T>::get_all_link_id(OutIt out_it)
	{
		for (auto it = m_links.begin(); it != m_links.end(); ++it)
			*out_it++ = it->first;
	}

	template<typename T>
	template<class OutIt>
	inline void Graph<T>::get_all_link_ptr(OutIt out_it)
	{
		for (auto it = m_links.begin(); it != m_links.end(); ++it)
			*out_it++ = it->second;
	}

	/////////////////////// Node //////////////////////////

	template <typename T>
	int Node<T>::id() const
	{
		return m_id;
	}

	template <typename T>
	T Node<T>::get_data() const
	{
		return m_data;
	}

	template <typename T>
	void Node<T>::set_data(const T& data)
	{
		m_data = data;
	}

	template <typename T>
	Node<T>::Links<T> & Node<T>::get_links()
	{
		return m_links;
	}

	template <typename T>
	const Node<T>::Links<T> & Node<T>::get_links() const
	{
		return m_links;
	}

	/////////////////////// Link //////////////////////////

	template <typename T>
	int Link<T>::id() const
	{
		return m_id;
	}

	template <typename T>
	int Link<T>::get_weight() const
	{
		return m_weight;
	}

	template <typename T>
	void Link<T>::set_weight(int weight)
	{
		m_weight = weight;
	}

	template <typename T>
	std::pair<NodePtr<T>, NodePtr<T>> Link<T>::get_nodes() const
	{
		if (!m_first_node.expired() && !m_second_node.expired())
			return std::pair<NodePtr<T>, NodePtr<T>>(m_first_node.lock(), m_second_node.lock());

		return std::pair<NodePtr<T>, NodePtr<T>>(nullptr, nullptr);
	}

	template <typename T>
	void Link<T>::set_nodes(std::pair<NodePtr<T>, NodePtr<T>> nodes)
	{
		if (nodes.first != nullptr && nodes.second != nullptr)
		{
			m_first_node.reset();
			m_first_node = std::weak_ptr<Node<T>>(nodes.first);
			m_second_node.reset();
			m_second_node = std::weak_ptr<Node<T>>(nodes.second);
		}
	}

	template <typename T>
	NodePtr<T> Link<T>::get_first_node() const
	{
		return m_first_node.expired() ? nullptr : m_first_node.lock();
	}

	template <typename T>
	void Link<T>::set_first_node(NodePtr<T> node)
	{
		m_first_node.reset();
		m_first_node = std::weak_ptr<Node<T>>(node);
	}

	template <typename T>
	NodePtr<T> Link<T>::get_second_node() const
	{
		return m_second_node.expired() ? nullptr : m_second_node.lock();
	}

	template <typename T>
	void Link<T>::set_second_node(NodePtr<T> node)
	{
		m_second_node.reset();
		m_second_node = std::weak_ptr<Node<T>>(node);
	}
}