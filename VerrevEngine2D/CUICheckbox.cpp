#include "CUICheckbox.h"
#include "CInput.h"

void CUICheckBox::init(CD2DRenderer *r, UI_ELEMENT_DESC *desc)
{
	UI_CHECKBOX_DESC *d = reinterpret_cast<UI_CHECKBOX_DESC*>(desc);
	mRenderer = r;
	id = d->id;
	mX = d->x;
	mY = d->y;
	mSize = d->size;
	mIsChecked = d->checked;
	mBrushName = "background-brush"; mBrushName += id;
	mCheckBrushName = "check-brush"; mCheckBrushName += id;

	mRenderer->addSolidBrush(mBrushName, d->backgroundColor);
	mRenderer->addSolidBrush(mCheckBrushName, d->checkColor);
}

bool CUICheckBox::isCursorInBounds(const int &x, const int &y)
{
	return x >= mX && x <= mX + mSize && y >= mY && y <= mY + mSize;
}

void CUICheckBox::draw()
{
	mRenderer->fillRect(mX, mY, mSize, mSize, mBrushName);
	if (mIsChecked) {
		float f = mSize / 8;
		mRenderer->fillRect(mX + f, mY + f, mSize - 2 * f, mSize - 2 * f, mCheckBrushName);
	}
}

void CUICheckBox::notify(CSubject *subject)
{
	CInput *i = static_cast<CInput*>(subject);
	if (i->mKeys[VK_LBUTTON]) {
		if (isCursorInBounds(i->mX, i->mY) && !mStillDown) {
			mStillDown = 1;
			mIsChecked = !mIsChecked;
		}
	}
	else {
		mStillDown = 0;
	}
}