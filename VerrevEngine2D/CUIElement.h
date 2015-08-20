#pragma once

#include <string>
#include <functional>
#include "CD2DRenderer.h"
#include "CObserver.h"

struct UI_ELEMENT_DESC
{
	std::string id;
};

class CUIElement
{
public:
	CUIElement() {}
	virtual ~CUIElement() {}
	inline std::string getID() const { return id; }

	virtual void init(CD2DRenderer *r, UI_ELEMENT_DESC *desc) = 0;
	virtual bool isCursorInBounds(const int &x, const int &y) = 0;
	virtual void draw() = 0;
protected:
	std::string id;
	CD2DRenderer *mRenderer;
};

