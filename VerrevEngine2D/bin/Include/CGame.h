#pragma once

#include <windows.h>
#include "CStateMachine.h"
#include "CStateFactory.h"

class CGame
{
public:
	bool setState(const UINT &id, UINT_PTR data = 0);
	bool setStateFactory(CStateFactory *stateFactory);
protected:
	CStateMachine mStateMachine;
	CStateFactory *mStateFactory;
};