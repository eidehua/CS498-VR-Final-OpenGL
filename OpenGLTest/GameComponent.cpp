#include "stdafx.h"
#include "GameComponent.h"

/**
* Standard Constructor,
* @param int (type of gamecomponent)
* @param bool (can a game object have more than one)
**/
GameComponent::GameComponent(int type, bool can_doubles)
{
	this->type = type;
	this->can_doubles = can_doubles;
}

/**
* Get function for its type
* @return int (type)
**/
int GameComponent::get_type()
{
	return this->type;
}

wchar_t * GameComponent::get_type_name()
{
	int type = this->get_type();
	switch (type){
	case NOTYPE:
		return L"NOTYPE";
		break;
	case TRANSFORM:
		return L"TRANSFORM";
		break;
	case MODEL:
		return L"MODEL";
		break;
	}
}

/**
* Get function for can_doubles
* @return bool
**/
bool GameComponent::get_can_doubles()
{
	return this->can_doubles;
}