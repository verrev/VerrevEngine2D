#include "CStateMachine.h"
#include "CState.h"

bool CStateMachine::setState(CState *state, CGame *game, const UINT &id, UINT_PTR data)
{
	if (!removeCurState(game)) return false;
	mCurState = state;
	if (!state) return true;
	mCurState->mId = id;
	mCurState->init(game, data);
	return true;
}

bool CStateMachine::removeCurState(CGame *game)
{
	if (!mCurState) return true;
	mCurState->destroy(game);
	delete mCurState;
	mCurState = nullptr;
	return true;
}