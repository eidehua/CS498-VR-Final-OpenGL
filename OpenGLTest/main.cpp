#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "OpenGL.h"
#include "Scene.h"
#include "Vertex.h"

// http://www.codeproject.com/Articles/26949/Xbox-Controller-Input-in-C-with-XInput
#include "CXBOXController.h"
#include <iostream>

/*
XINPUT_GAMEPAD_DPAD_UP          0x00000001
XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
XINPUT_GAMEPAD_START            0x00000010
XINPUT_GAMEPAD_BACK             0x00000020
XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
XINPUT_GAMEPAD_A                0x1000
XINPUT_GAMEPAD_B                0x2000
XINPUT_GAMEPAD_X                0x4000
XINPUT_GAMEPAD_Y                0x8000




typedef struct _XINPUT_GAMEPAD {
WORD wButtons;
BYTE bLeftTrigger;
BYTE bRightTrigger;
SHORT sThumbLX;
SHORT sThumbLY;
SHORT sThumbRX;
SHORT sThumbRY;
} XINPUT_GAMEPAD, *PXINPUT_GAMEPAD;
*/


#define BUFFER_OFFSET(i) ((void*)(i))

using namespace std;

Debug debug;

OpenGL opengl;
Scene scene;

CXBOXController* Player1;

void update() {
	scene.render_scene(&opengl);
}

int main(int argc, char* argv[])
{
	debug.init(debug.VERBOSE);
	Player1 = new CXBOXController(1);
	glutInit(&argc, argv);

	opengl.init(1600, 700);

	GameObject *box = new GameObject();
	Model *model = new Model();
	model->init_from_obj_file(L"square.obj");
	box->add_game_component((GameComponent *) model);

	opengl.init_buffer(model->vertexBuffer, model->verts, GL_ARRAY_BUFFER);
	opengl.init_buffer(model->indiciesBuffer, model->indices, GL_ELEMENT_ARRAY_BUFFER);
	opengl.bind_vertex_indices(model);

	scene.add_game_object(box);

	glutDisplayFunc(update);

	glutMainLoop();

	/*while (true)
	{
		if (Player1->IsConnected())
		{	
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				Player1->Vibrate(0, 65535);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				Player1->Vibrate(65535, 65535);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				Player1->Vibrate();
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				break;
			}
		}
		else
		{
			std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
			std::cout << "Press Any Key To Exit.";
			std::cin.get();
			break;
		}
	}*/

	return 0;
}