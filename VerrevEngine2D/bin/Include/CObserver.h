#pragma once

class CSubject;

class CObserver
{
public:
	CObserver() {}
	virtual ~CObserver() {}
	virtual void notify(CSubject *subject) = 0;
};