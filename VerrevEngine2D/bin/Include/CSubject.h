#pragma once

#include <vector>
#include "CObserver.h"

class CSubject
{
public:
	CSubject() {}
	virtual ~CSubject() {}
	void registerObserver(CObserver *o) { mObservers.push_back(o); }
	void unRegisterObserver(CObserver *o) { mObservers.erase(std::find(mObservers.begin(), mObservers.end(), o)); }
	virtual void notifyObservers() = 0;
public:
	std::vector<CObserver*> mObservers;
};
