#include "Objects.h"

#include <ostream>

using namespace std;

///////////////////////// BaseObject /////////////////////////

BaseObject::~BaseObject() 
{}

int BaseObject::id() const
{
	return m_id;
}

void BaseObject::set_id(const int id)
{
	m_id = id;
}

int BaseObject::number() const
{
	return m_number;
}

void BaseObject::set_number(const int number)
{
	m_number = number;
}

void BaseObject::print(std::ostream & out) const
{
	out << "BaseObject[" << m_id << ']' << endl;
}

void BaseObject::draw(std::ostream & out) const
{
	out << '?';
}

BaseObjPtr BaseObject::clone() const
{
	return make_shared<BaseObject>(*this);
}

///////////////////////// Ball /////////////////////////

Ball::Ball(const int id, const int number)
{
	m_id = id;
	m_number = number;
}

void Ball::print(ostream & out_stream) const
{
	out_stream << "Ball[" << m_id << ']' << endl;
}

void Ball::draw(std::ostream & out_stream) const
{
	out_stream << '*';
}

BaseObjPtr Ball::clone() const
{
	return make_shared<Ball>(*this);
}

///////////////////////// Hole /////////////////////////

Hole::Hole(int id, const int number)
{
	m_id = id;
	m_ball = nullptr;
	m_is_closed = false;
	m_number = number;
}

Hole::Hole(const Hole & hole)
{
	if (this == &hole)
		return;

	m_id = hole.id();
	m_number = hole.number();
	m_is_closed = hole.is_closed();

	if (hole.m_ball)
		m_ball = make_shared<Ball>(*hole.m_ball.get());
	else
		m_ball = nullptr;
}

void Hole::push_ball(BallPtr ball)
{
	m_ball = ball;
	m_is_closed = true;
}

BallPtr Hole::pop_ball()
{
	BallPtr ball = m_ball;

	m_ball.reset();
	m_ball = nullptr;
	m_is_closed = false;

	return ball;
}

BallPtr Hole::get_ball() const
{
	return m_ball;
}

bool Hole::is_closed() const
{
	return m_is_closed;
}

void Hole::print(std::ostream & out_stream) const
{
	out_stream << "Hole[" << m_id << "] ";

	if (m_ball)
		m_ball->print(out_stream);
	else out_stream << endl;
}

void Hole::draw(std::ostream & out_stream) const
{
	if (m_is_closed)
		out_stream << 'X';
	else
		out_stream << 'O';
}

BaseObjPtr Hole::clone() const
{
	return make_shared<Hole>(*this);
}

Hole & Hole::operator=(const Hole & hole)
{
	if (this == &hole)
		return *this;

	m_id = hole.id();
	m_number = hole.number();
	m_is_closed = hole.is_closed();

	if (hole.m_ball)
		m_ball = make_shared<Ball>(*hole.m_ball.get());
	else
		m_ball = nullptr;

	return *this;
}

///////////////////////// Wall /////////////////////////

Wall::Wall(int id, const int number)
{
	m_id = id;
	m_number = number;
}

void Wall::print(std::ostream & out_stream) const
{
	out_stream << "Wall[" << m_id << ']' << endl;
}

void Wall::draw(std::ostream & out_stream) const
{
	out_stream << '#';
}

BaseObjPtr Wall::clone() const
{
	return make_shared<Wall>(*this);
}
