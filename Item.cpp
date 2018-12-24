#include "Item.h"

// Player::Player(Vec2 position) : Entity(position, "images/player_ship.png")

Item::Item(Vec2 position, std::string image) : Entity(position, image) {}


Item::~Item()
{
}
