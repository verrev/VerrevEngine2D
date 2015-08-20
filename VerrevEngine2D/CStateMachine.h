#pragma once

#include <windows.h>

class CState;
class CGame;

class CStateMachine
{
public:
	bool setState(CState *state, CGame *game, const UINT &id, UINT_PTR data = 0);
	bool removeCurState(CGame *game);
public:
	CState *mCurState;
};