#pragma once

#include <windows.h>
#include <d2d1_1.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")
#include <string>
#include <map>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <wincodec.h>
#pragma comment(lib, "windowscodecs.lib")

class CD2DRenderer
{
public:
	template<typename T>
	inline void safeRelease(T& ptr)
	{
		if (ptr != NULL) {
			ptr->Release();
			ptr = NULL;
		}
	}
	CD2DRenderer() { factory = nullptr; renderTarget = nullptr; dwriteFactory = nullptr; currentBrush = nullptr; }
	~CD2DRenderer()
	{
		for (auto i = brushes.begin(); i != brushes.end(); ++i) safeRelease(i->second);
		brushes.clear();

		for (auto i = fonts.begin(); i != fonts.end(); ++i) safeRelease(i->second);
		fonts.clear();

		for (auto i = bitmaps.begin(); i != bitmaps.end(); ++i) safeRelease(i->second);
		bitmaps.clear();

		safeRelease(factory); safeRelease(renderTarget); safeRelease(dwriteFactory);
	}
public:
	bool init(HWND windowHandle);
	bool init(HWND windowHandle, IDXGISwapChain *swapChain);

	inline ID2D1RenderTarget *getRenderTarget() const { return renderTarget; }
	inline IDWriteFactory *getDwriteFactory() const { return dwriteFactory; }

	void beginDraw() const { renderTarget->BeginDraw(); }
	void endDraw() const { renderTarget->EndDraw(); }
	void clearScreen(const float &r, const float &g, const float &b) const;

	void setBrush(const std::string &brushName);
	void addBrush(ID2D1Brush *brush, const std::string &brushName);
	void addSolidBrush(const std::string &brushName, const D2D1::ColorF &color);
	void removeBrush(const std::string &brushName);

	void setFont(const std::string &fontName);
	void addFont(IDWriteTextFormat *font, const std::string &fontName);
	void addFont(const std::string &fontID, const std::wstring &fontName, const float &size, const bool &centerHorizontally = true, const bool &centerVertically = true);
	IDWriteTextFormat *getFont(const std::string &fontName) { return fonts[fontName]; }
	void removeFont(const std::string &fontName);

	void addBitmap(const std::string &bitmapName, const std::wstring &path);
	void removeBitmap(const std::string &bitmapName);

public:
	void drawEllipse(const float &x, const float &y, const float &radiusX, const float &radiusY, const float &thickness, const std::string &brushName = "");
	void fillEllipse(const float &x, const float &y, const float &radiusX, const float &radiusY, const std::string &brushName = "");

	void drawCircle(const float &x, const float &y, const float &radius, const float &thickness, const std::string &brushName = "");
	void fillCircle(const float &x, const float &y, const float &radius, const std::string &brushName = "");

	void drawRect(const float &x, const float &y, const float &w, const float &h, const float &thickness, const std::string &brushName = "");
	void fillRect(const float &x, const float &y, const float &w, const float &h, const std::string &brushName = "");

	void drawRoundedRect(const float &x, const float &y, const float &w, const float &h, const float &radiusX, const float &radiusY, const float &thickness, const std::string &brushName = "");
	void fillRoundedRect(const float &x, const float &y, const float &w, const float &h, const float &radiusX, const float &radiusY, const std::string &brushName = "");

	void drawLine(const float &x, const float &y, const float &x2, const float &y2, const float &thickness, const std::string &brushName = "");

	void drawText(const std::wstring &text, const float &x, const float &y, const float &w, const float &h, const std::string &brushName = "", const std::string &fontName = "");

	void drawBitmap(const std::string &bitmapName, const float &x, const float &y);

	inline D2D1_SIZE_F CD2DRenderer::getBitmapSize(const std::string &bitmapName)
	{
		return bitmaps[bitmapName]->GetSize();
	}
private:
	ID2D1Bitmap *loadBitmapFromFile(const std::wstring &path);
	IWICImagingFactory *wicFactory;
private:
	ID2D1Factory *factory;
	ID2D1RenderTarget *renderTarget;
	IDWriteFactory *dwriteFactory;

	ID2D1Brush *currentBrush;
	std::map <std::string, ID2D1Brush*> brushes;

	IDWriteTextFormat *currentFont;
	std::map <std::string, IDWriteTextFormat*> fonts;

	std::map <std::string, ID2D1Bitmap*> bitmaps;
};

