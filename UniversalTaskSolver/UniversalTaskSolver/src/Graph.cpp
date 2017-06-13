#include "Graph.h"

using namespace grp;
using namespace std;

/////////////////////// Graph //////////////////////////

grp::Graph::Graph() : m_node_id_counter(0), m_link_id_counter(0)
{}

NodePtr grp::Graph::create_node(const int data)
{
	NodePtr node = make_shared<Node>(get_new_node_id());
	node->set_data(data);

	m_nodes[node->id()] = node;
	return node;
}

LinkPtr grp::Graph::create_link()
{
	LinkPtr link = make_shared<Link>(get_new_link_id());
	m_links[link->id()] = link;
	return link;
}

LinkPtr grp::Graph::create_link(const NodePtr first_node, const NodePtr second_node, int weight)
{
	if (m_nodes.find(first_node->id()) == m_nodes.end() ||
		m_nodes.find(second_node->id()) == m_nodes.end())
		return nullptr;
	
	LinkPtr link = make_shared<Link>(get_new_link_id());
	link->set_weight(weight);
	link->set_first_node(first_node);
	link->set_second_node(second_node);

	m_links[link->id()] = link;
	return link;
}

LinkPtr grp::Graph::create_link(int first_node_id, int second_node_id, int weight)
{
	NodePtr first_node = nullptr;
	auto first_it = m_nodes.find(first_node_id);
	if (first_it != m_nodes.end())
		first_node = first_it->second;

	NodePtr second_node = nullptr;
	auto second_it = m_nodes.find(second_node_id);
	if (second_it != m_nodes.end())
		second_node = second_it->second;

	LinkPtr link = make_shared<Link>(get_new_link_id());
	link->set_weight(weight);
	link->set_first_node(first_node);
	link->set_second_node(second_node);

	m_links[link->id()] = link;
	return link;
}

void grp::Graph::reset()
{
	m_nodes.clear();
	m_links.clear();
	m_link_id_counter = 0;
	m_node_id_counter = 0;
}

bool grp::Graph::delete_node(int node_id)
{
	auto it = m_nodes.find(node_id);
	if (it != m_nodes.end())
	{
		m_nodes.erase(it);
		return true;
	}

	return false;
}

void grp::Graph::delete_all_nodes()
{
	m_nodes.clear();
}

bool grp::Graph::delete_link(int link_id)
{
	auto it = m_links.find(link_id);
	if (it != m_links.end())
	{
		m_links.erase(it);
		return true;
	}

	return false;
}

void grp::Graph::delete_all_links()
{
	m_links.clear();
}

bool grp::Graph::exist_node(int node_id) const
{
	return m_nodes.find(node_id) != m_nodes.end();
}

bool grp::Graph::exist_node(const NodePtr node) const
{
	if (node == nullptr)
		return false;

	return m_nodes.find(node->id()) != m_nodes.end();
}

bool grp::Graph::exist_link(int link_id) const
{
	return m_links.find(link_id) != m_links.end();
}

bool grp::Graph::exist_link(const LinkPtr link) const
{
	if (link == nullptr)
		return false;

	return m_links.find(link->id()) != m_links.end();
}

unsigned grp::Graph::get_node_count() const
{
	return m_nodes.size();
}

unsigned grp::Graph::get_link_count() const
{
	return m_links.size();
}

NodePtr grp::Graph::get_node(int node_id)
{
	auto it = m_nodes.find(node_id);
	if (it != m_nodes.end())
		return it->second;

	return nullptr;
}

const NodePtr grp::Graph::get_node(int node_id) const
{
	auto it = m_nodes.find(node_id);
	if (it != m_nodes.end())
		return it->second;

	return nullptr;
}

LinkPtr grp::Graph::get_link(int link_id)
{
	auto it = m_links.find(link_id);
	if (it != m_links.end())
		return it->second;

	return nullptr;
}

const LinkPtr grp::Graph::get_link(int link_id) const
{
	auto it = m_links.find(link_id);
	if (it != m_links.end())
		return it->second;

	return nullptr;
}

int grp::Graph::get_new_node_id()
{
	return m_node_id_counter++;
}

int grp::Graph::get_new_link_id()
{
	return m_link_id_counter++;
}


/////////////////////// Node //////////////////////////

int grp::Node::id() const
{
	return m_id;
}

int grp::Node::get_data() const
{
	return m_data;
}

void grp::Node::set_data(int data)
{
	m_data = data;
}

grp::Node::Links & grp::Node::get_links()
{
	return m_links;
}

const grp::Node::Links & grp::Node::get_links() const
{
	return m_links;
}

/////////////////////// Link //////////////////////////

int grp::Link::id() const
{
	return m_id;
}

int grp::Link::get_weight() const
{
	return m_weight;
}

void grp::Link::set_weight(int weight)
{
	m_weight = weight;
}

std::pair<NodePtr, NodePtr> grp::Link::get_nodes() const
{
	if (!m_first_node.expired() && !m_second_node.expired())
		return std::pair<NodePtr, NodePtr>(m_first_node.lock(), m_second_node.lock());

	return std::pair<NodePtr, NodePtr>(nullptr, nullptr);
}

void grp::Link::set_nodes(std::pair<NodePtr, NodePtr> nodes)
{
	if (nodes.first != nullptr && nodes.second != nullptr)
	{
		m_first_node.reset();
		m_first_node = weak_ptr<Node>(nodes.first);
		m_second_node.reset();
		m_second_node = weak_ptr<Node>(nodes.second);
	}
}

NodePtr grp::Link::get_first_node() const
{
	return m_first_node.expired() ? nullptr : m_first_node.lock();
}

void grp::Link::set_first_node(NodePtr node)
{
	m_first_node.reset();
	m_first_node = weak_ptr<Node>(node);
}

NodePtr grp::Link::get_second_node() const
{
	return m_second_node.expired() ? nullptr : m_second_node.lock();
}

void grp::Link::set_second_node(NodePtr node)
{
	m_second_node.reset();
	m_second_node = weak_ptr<Node>(node);
}