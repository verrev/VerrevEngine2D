#include "CUITextBox.h"
#include "CInput.h"

void CUITextBox::init(CD2DRenderer *r, UI_ELEMENT_DESC *desc)
{
	UI_TEXTBOX_DESC *d = reinterpret_cast<UI_TEXTBOX_DESC*>(desc);
	mRenderer = r;
	mIsWriting = 0;
	id = d->id;
	mX = d->x;
	mY = d->y;
	mW = d->w;
	mH = d->h;
	mText = d->text;
	mCenterH = d->centerH;
	mCenterV = d->centerV;
	mFontSize = d->fontSize;
	mOnInsert = d->onInsert;

	mBrushName = "background-brush"; mBrushName += id;
	mTextBrushName = "text-brush"; mTextBrushName += id;
	mCursorBrushName = "cursor-brush"; mCursorBrushName += id;

	mRenderer->addSolidBrush(mBrushName, d->backgroundColor);
	mRenderer->addSolidBrush(mTextBrushName, d->textColor);
	mRenderer->addSolidBrush(mCursorBrushName, D2D1::ColorF(0, 0, 0, 1));

	mFontName = "button-font"; mFontName += id;
	mRenderer->addFont(mFontName, L"Helvetica", mFontSize, mCenterH, mCenterV);
}

bool CUITextBox::isCursorInBounds(const int &x, const int &y)
{
	return x >= mX && x <= mX + mW && y >= mY && y <= mY + mH;
}

void CUITextBox::draw()
{
	mRenderer->fillRect(mX, mY, mW, mH, mBrushName);
	mRenderer->drawText(mText, mX + 1, mY + 1, mW - 1, mH - 1, mTextBrushName, mFontName);
	if (mIsWriting) {
		//g->fillRect(x, y + h / 8, h / 2, h - h / 4, cursorBrushName);
	}
}

void CUITextBox::notify(CSubject *subject)
{
	CInput *i = static_cast<CInput*>(subject);
	if (i->mKeys[VK_LBUTTON]) {
		if (isCursorInBounds(i->mX, i->mY)) mIsWriting = 1;
		else mIsWriting = 0;
	}
	if (mIsWriting && !i->mKeys[VK_RETURN]) {
		std::string s = "";
		
		for (int j = 48; j < 90; ++j) {
			if (i->mKeys[j] && !mStillDown[j]) {
				mStillDown[j] = 1;
				s += tolower(j);
			}
			else if (!i->mKeys[j]) {
				mStillDown[j] = 0;
			}
		}
			
		if (i->mKeys[VK_OEM_MINUS] && !mStillDown[VK_OEM_MINUS]) {
			mStillDown[VK_OEM_MINUS] = 1;
			s += "-";
		}
		else if (!GetAsyncKeyState(VK_OEM_MINUS)) {
			mStillDown[VK_OEM_MINUS] = 0;
		}

		if (i->mKeys[VK_SPACE] && !mStillDown[VK_SPACE]) {
			mStillDown[VK_SPACE] = 1;
			s += " ";
		}
		else if (!GetAsyncKeyState(VK_SPACE)) {
			mStillDown[VK_SPACE] = 0;
		}

		mText += std::wstring(s.begin(), s.end());
		if ((i->mKeys[VK_BACK]) && !mStillDown[VK_BACK]) { mStillDown[VK_BACK] = 1; if (mText.size()) mText.erase(mText.end() - 1); }
		else if (!GetAsyncKeyState(VK_BACK)) { mStillDown[VK_BACK] = 0; }
	}
	else if (i->mKeys[VK_RETURN]) {
		mIsWriting = 0;
		if (mOnInsert) mOnInsert();
	}
}
