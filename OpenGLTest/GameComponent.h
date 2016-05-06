#pragma once

class GameComponent {
	public:
		//GameComponets type
		static const int NOTYPE = 0;
		static const int TRANSFORM = 1;
		static const int MODEL = 2;

		//Constructor
		GameComponent(int type, bool can_doubles);

		//Getters - No setters because they should never change
		int get_type();
		wchar_t * get_type_name();
		bool get_can_doubles();

	private:
		//Basic attributes
		int type = 0;
		bool can_doubles = 0; //Determines if a gameobject can have two of the same game componets
};