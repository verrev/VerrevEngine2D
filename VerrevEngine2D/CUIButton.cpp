#include "CUIButton.h"
#include "CInput.h"

void CUIButton::init(CD2DRenderer *r, UI_ELEMENT_DESC *desc)
{
	mRenderer = r;
	UI_BUTTON_DESC *d = reinterpret_cast<UI_BUTTON_DESC*>(desc);
	id = d->id;
	mX = d->x;
	mY = d->y;
	mW = d->w;
	mH = d->h;
	mText = d->text;
	mCenterH = d->centerH;
	mCenterV = d->centerV;
	mFontSize = d->fontSize;
	mOnClick = d->onClick;

	mBrushName = "background-brush"; mBrushName += id;
	mTextBrushName = "text-brush"; mTextBrushName += id;

	mRenderer->addSolidBrush(mBrushName, d->backgroundColor);
	mRenderer->addSolidBrush(mTextBrushName, d->textColor);

	mFontName = "button-font"; mFontName += id;
	mRenderer->addFont(mFontName, L"Helvetica", mFontSize, mCenterH, mCenterV);
}

bool CUIButton::isCursorInBounds(const int &x, const int &y)
{
	return x >= mX && x <= mX + mW && y >= mY && y <= mY + mH;
}

void CUIButton::draw()
{
	mRenderer->fillRect(mX, mY, mW, mH, mBrushName);
	mRenderer->drawText(mText, mX + 1, mY + 1, mW - 1, mH - 1, mTextBrushName, mFontName);
}

void CUIButton::notify(CSubject *subject)
{
	CInput *i = static_cast<CInput*>(subject);
	if (i->mKeys[VK_LBUTTON]) {
		if (isCursorInBounds(i->mX, i->mY) && !mStillDown) {
			mStillDown = 1;
			if (mOnClick) mOnClick();
		}
	}
	else {
		mStillDown = 0;
	}
}