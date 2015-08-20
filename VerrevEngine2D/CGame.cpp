#include "CGame.h"

bool CGame::setState(const UINT &id, UINT_PTR data)
{
	CState *newState = mStateFactory->getState(id);
	return mStateMachine.setState(newState, this, id, data);
}

bool CGame::setStateFactory(CStateFactory *stateFactory)
{
	mStateFactory = stateFactory;
	if (mStateFactory) return 1;
	return 0;
}

