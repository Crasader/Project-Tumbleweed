#pragma once
#include "GameObject.h"
#include "XinputManager.h"
namespace Sedna {


	enum playerNumber {

		playerOne = 1,
		playerTwo

	};
class Player : public GameObject
{
public:
	Player() {}
	Player(int wPlayer, float x, float y);
	~Player();

	//extend member functions here
	
	void shoot();
private:


};

}
