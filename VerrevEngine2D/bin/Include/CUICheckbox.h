#pragma once

#include "CUIElement.h"

struct UI_CHECKBOX_DESC : public UI_ELEMENT_DESC
{
	UI_CHECKBOX_DESC(const std::string &_id, const float &posX, const float &posY, const float &sideLength, const D2D1::ColorF &background, const D2D1::ColorF &check, const bool &isChecked) :
		x(posX), y(posY), size(sideLength), backgroundColor(background), checked(isChecked), checkColor(check) {
		id = _id;
	}
	float x, y, size;
	bool checked;
	D2D1::ColorF backgroundColor, checkColor;
};

class CUICheckBox : public CUIElement, public CObserver
{
public:
	CUICheckBox() {}
	~CUICheckBox() {}
	void init(CD2DRenderer *r, UI_ELEMENT_DESC *desc) override;
	bool isCursorInBounds(const int &x, const int &y) override;
	void draw() override;
	void notify(CSubject *subject) override;
	
	inline bool isChecked() const { return mIsChecked; }
private:
	float mX, mY, mSize;
	bool mIsChecked;
	std::string mBrushName, mCheckBrushName;
	bool mStillDown = 0;
};

