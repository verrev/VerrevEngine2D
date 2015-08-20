#pragma once

#include "CSubject.h"
#include <vector>
#include <windows.h>

class CInput : public CSubject
{
public:
	CInput() {}
	virtual ~CInput() {}
	void notifyObservers() override;
	void update();
public:
	UINT mX, mY;
	bool mKeys[256];
	HWND mWindow;
};