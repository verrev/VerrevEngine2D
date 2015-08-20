#pragma once

#include "CUIElement.h"
#include "CSubject.h"

struct UI_BUTTON_DESC : public UI_ELEMENT_DESC
{
	UI_BUTTON_DESC(const std::string &btnID, const float &posX, const float &posY, const float &width, const float &height, const D2D1::ColorF &background, const D2D1::ColorF &textColor, const std::wstring &btnText, const float &_fontSize, std::function<void()> onClickFunc = nullptr, const bool &centerHorizontally = true, const bool &centerVertically = true) :
		x(posX), y(posY), w(width), h(height), backgroundColor(background), textColor(textColor), text(btnText), fontSize(_fontSize), centerH(centerHorizontally), centerV(centerVertically), onClick(onClickFunc) {
		id = btnID;
	}
	float x, y, w, h;
	float fontSize;
	bool centerH, centerV;
	D2D1::ColorF backgroundColor, textColor;
	std::wstring text;
	std::function<void()> onClick;
};

class CUIButton : public CUIElement, public CObserver
{
public:
	CUIButton() {}
	~CUIButton() {}
	void init(CD2DRenderer *r, UI_ELEMENT_DESC *desc) override;
	bool isCursorInBounds(const int &x, const int &y) override;
	void draw() override;
	void notify(CSubject *subject) override;

	inline void setText(const std::wstring &text) { mText = text; }
	inline std::wstring &getText() { return mText; }
private:
	float mX, mY, mW, mH;
	float mFontSize;
	bool mCenterH, mCenterV;
	std::wstring mText;
	std::string mBrushName, mFontName, mTextBrushName;
	std::function<void()> mOnClick;
	bool mStillDown = 0;
};

