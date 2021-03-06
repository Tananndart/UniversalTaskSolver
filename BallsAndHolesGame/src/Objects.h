#pragma once

#include <memory>

class BaseObject;
class Ball;
class Hole;
class Wall;

typedef std::shared_ptr<BaseObject> BaseObjPtr;
typedef std::shared_ptr<Ball> BallPtr;
typedef std::shared_ptr<Hole> HolePtr;
typedef std::shared_ptr<Wall> WallPtr;

enum EnObjects {BALL, HOLE, WALL};

class BaseObject
{
public:
	virtual ~BaseObject();
	
	virtual int id() const;
	virtual void set_id(const int id);

	virtual int number() const;
	virtual void set_number(const int number);

	virtual void print(std::ostream&) const;
	virtual void draw(std::ostream&) const;

	virtual BaseObjPtr clone() const;

protected:
	int m_id;
	int m_number;
};

class Ball : public BaseObject
{
public:
	Ball(const int id, const int number = 0);

	void print(std::ostream& out_stream) const override;
	void draw(std::ostream& out_stream) const override;

	BaseObjPtr clone() const override;
};

class Hole : public BaseObject
{
public:
	Hole(int id, const int number = 0);
	Hole(const Hole & hole);

	void push_ball(BallPtr ball);
	BallPtr pop_ball();
	BallPtr get_ball() const;

	bool is_closed() const;

	void print(std::ostream& out_stream) const override;
	void draw(std::ostream& out_stream) const override;

	BaseObjPtr clone() const override;

	Hole & operator=(const Hole & hole);

private:
	bool m_is_closed;
	BallPtr m_ball;
};

class Wall : public BaseObject
{
public:
	Wall(int id, const int number = 0);

	void print(std::ostream& out_stream) const override;
	void draw(std::ostream& out_stream) const override;

	BaseObjPtr clone() const override;
};