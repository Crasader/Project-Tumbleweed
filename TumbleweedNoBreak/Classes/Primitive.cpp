//Anthony Smiderle
//100695532
#include "Primitive.h"
#include "2d/CCDrawNode.h"

namespace Sedna {

	//kinda did this for fun, but it also tells us if the primitive is actually updating
	cocos2d::Color4F colourLerp(cocos2d::Color4F c1, cocos2d::Color4F c2, float dt) {

		cocos2d::Color4F temp;
		temp = cocos2d::Color4F((1.0f - dt)*c1.r + dt * c2.r, (1.0f - dt)*c1.g + dt * c2.g, (1.0f - dt)*c1.b + dt * c2.b, 1.0f);
		return temp;
	}

	SquarePrimitive::SquarePrimitive(const cocos2d::Vec2 & startingPosition, const cocos2d::Vec2 & endPosition)
		: Node(cocos2d::DrawNode::create())//initialize draw node
	{
		//draw a rectangle given dimensions
		p1 = startingPosition;
		p2 = endPosition;

		Node->drawSolidRect(p1, p2, colourLerp(cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f), cocos2d::Color4F(0.0f, 0.0f, 1.0f, 1.0f), 1.0f));

		velocity = cocos2d::Vec2(0, 0);
	}

	SquarePrimitive::SquarePrimitive()
	{
	}

	SquarePrimitive::~SquarePrimitive()
	{
	}
	cocos2d::DrawNode *  SquarePrimitive::getDrawNode() const
	{
		return Node;
	}

	cocos2d::Vec2  SquarePrimitive::getCentre()
	{
		return cocos2d::Vec2(p1.x + p2.x / 2, p1.y + p2.y / 2);
	}

	void  SquarePrimitive::addForce(cocos2d::Vec2 v,float dt)
	{
		velocity += v *dt;//create the illusion of acceleration

		update();
	}

	void  SquarePrimitive::update()
	{

		//values that we use in order to determine what dt should be (for lerp)
		if (dt > 0.9f || dt < 0.01f)
		{
			//make sure dt is either the largest or smallest it can be
			dt = dt > .9f ? .9f : 0.01f;

			//invert dt2
			dt2 *= -1;
		}

		dt += dt2;

		p1 += velocity;
		p2 += velocity;
		this->Node->clear();

		//draw the new rectangle at the new coordinates determined by adding the velocity to the two member vectors
		Node->drawSolidRect(p1, p2, colourLerp(cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f), cocos2d::Color4F(0.0f, 0.0f, 1.0f, 1.0f), dt));
	}

	void  SquarePrimitive::update(bool yn)
	{
		p1 += velocity;
		p2 += velocity;
		this->Node->clear();
		Node->drawSolidRect(p1, p2, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	}





	//Circle
	Sedna::CirclePrimitive::CirclePrimitive(const cocos2d::Vec2 &LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS)
		: Node(cocos2d::DrawNode::create()), location(LOCATION), radius(RADIUS), angle(ANGLE), segments(SEGMENTS)
	{
		//draw a circle given dimensions
		Node->drawCircle(LOCATION, RADIUS, ANGLE, SEGMENTS, false, colourLerp(cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f), cocos2d::Color4F(0.0f, 0.0f, 1.0f, 1.0f), 1.0f));
	}

	Sedna::CirclePrimitive::CirclePrimitive()
	{
	}

	Sedna::CirclePrimitive::~CirclePrimitive()
	{
	}

	cocos2d::DrawNode * Sedna::CirclePrimitive::getDrawNode() const
	{
		return Node;
	}

	void CirclePrimitive::update()
	{
		//same as square update really

		if (dt > 0.9f || dt < 0.01f)
		{
			dt = dt > .9f ? .9f : 0.01f;
			dt2 *= -1;
		}

		dt += dt2;

		location += velocity;
		Node->clear();
		Node->drawCircle(location, radius, angle, segments, false, colourLerp(cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f), cocos2d::Color4F(0.0f, 0.0f, 1.0f, 1.0f), dt));

	}

	void CirclePrimitive::addForce(float vX, float vY, float dt)
	{

		cocos2d::Vec2 v = cocos2d::Vec2(vX, vY);
		int maxVelocity = 4;
		int minVelocity = -4;

		//velocity is capped here

		velocity += v * dt;

		if (velocity.x >= maxVelocity)
			velocity.x = maxVelocity;
		else if (velocity.x <= minVelocity)
			velocity.x = minVelocity;
		if (velocity.y >= maxVelocity)
			velocity.y = maxVelocity;
		else if (velocity.y <= minVelocity)
			velocity.y = minVelocity;
	}

	void CirclePrimitive::setForce(cocos2d::Vec2 v, float dt)
	{
		velocity = v * dt;
	}

	void CirclePrimitive::setLocation(cocos2d::Vec2 p)
	{
		this->location = p;
	}

	cocos2d::Vec2 CirclePrimitive::getVelocity() const
	{
		return velocity;
	}

	cocos2d::Vec2 CirclePrimitive::getLocation() const
	{
		return location;
	}

	bool CirclePrimitive::checkCollision(CirclePrimitive other)
	{

		//get the length of the distance vector
		float distance = sqrt((this->location.x - other.location.x)*(this->location.x - other.location.x) +
			(this->location.y - other.location.y)*(this->location.y - other.location.y));


		if (distance <= (this->radius + other.radius))
			return true;

		return false;
	}

	bool CirclePrimitive::checkTouching(CirclePrimitive other)
	{
		float distance = sqrt((this->location.x - other.location.x)*(this->location.x - other.location.x) +
			(this->location.y - other.location.y)*(this->location.y - other.location.y));

		//if they are exactly touching, return true
		if (distance == (this->radius + other.radius))
			return true;
		return false;
	}



	bool CirclePrimitive::checkCloseTouching(CirclePrimitive other)
	{
		float distance = sqrt((this->location.x - other.location.x)*(this->location.x - other.location.x) +
			(this->location.y - other.location.y)*(this->location.y - other.location.y));


		//if they are VERY close to touching return true
		if (distance <= ((this->radius - (this->radius / 10)) + (other.radius - (other.radius / 10))))
			return true;
		return false;
	}

}