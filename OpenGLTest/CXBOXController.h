#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

#include <windows.h>
#include <XInput.h>


#pragma comment(lib, "XINPUT9_1_0.lib")

// XBOX Controller Class Definition
class CXBOXController
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;
public:
	CXBOXController(int playerNumber);
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);
};

#endif