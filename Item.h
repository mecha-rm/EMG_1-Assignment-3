#pragma once
#include "Entity.h"

#include <iostream>

class Item : public Entity
{
public:
	Item(Vec2 poisition, std::string);
	~Item();
};

