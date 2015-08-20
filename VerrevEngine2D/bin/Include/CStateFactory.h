#pragma once

#include <windows.h>

class CState;

class CStateFactory
{
public:
	virtual CState *getState(const UINT &id) const = 0;
};