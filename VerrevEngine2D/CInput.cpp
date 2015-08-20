#include "CInput.h"

void CInput::update()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(mWindow, &p);
	mX = p.x;
	mY = p.y;
	for (int i = 0; i < 256; ++i) mKeys[i] = GetAsyncKeyState(i);
	notifyObservers();
}

void CInput::notifyObservers()
{
	for (auto o : mObservers) o->notify(this);
}
