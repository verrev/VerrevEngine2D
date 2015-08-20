#pragma once

#include "CUIElement.h"

struct UI_TEXTBOX_DESC : public UI_ELEMENT_DESC
{
	UI_TEXTBOX_DESC(const std::string &_id, const float &posX, const float &posY, const float &width, const float &height, const D2D1::ColorF &background, const D2D1::ColorF &textColor, const std::wstring &initialText, const float &_fontSize, std::function<void()> onInsertPressed = nullptr, const bool &centerHorizontally = true, const bool &centerVertically = true) :
		x(posX), y(posY), w(width), h(height), backgroundColor(background), textColor(textColor), text(initialText), fontSize(_fontSize), centerH(centerHorizontally), centerV(centerVertically), onInsert(onInsertPressed) {
		id = _id;
	}
	float x, y, w, h;
	float fontSize;
	bool centerH, centerV;
	D2D1::ColorF backgroundColor, textColor;
	std::wstring text;
	std::function<void()> onInsert;
};

class CUITextBox : public CUIElement, public CObserver
{
public:
	CUITextBox() {}
	~CUITextBox() {}
	void init(CD2DRenderer *r, UI_ELEMENT_DESC *desc) override;
	bool isCursorInBounds(const int &x, const int &y) override;
	void draw() override;
	void notify(CSubject *subject) override;

	inline void setText(const std::wstring &text) { mText = text; }
	inline std::wstring &getText() { return mText; }
public:
	bool mIsWriting;
private:
	float mX, mY, mW, mH;
	float mFontSize;
	bool mCenterH, mCenterV;
	std::wstring mText;
	std::string mBrushName, mFontName, mTextBrushName, mCursorBrushName;
	bool mStillDown[256] = { 0 };
	std::function<void()> mOnInsert;
};

