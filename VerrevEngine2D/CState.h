#pragma once
#include <windows.h>

class CGame;

class CState
{
	friend class CStateMachine;
public:
	CState() {}
	virtual ~CState() {}
	virtual void init(CGame *game, UINT_PTR data = 0) = 0;
	virtual void destroy(CGame *game) = 0;
	virtual void update(CGame *game) = 0;
	virtual void draw(CGame *game) = 0;
protected:
	UINT mId;
};

