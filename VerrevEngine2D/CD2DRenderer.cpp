#include "CD2DRenderer.h"

bool CD2DRenderer::init(HWND windowHandle)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (hr != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	ID2D1HwndRenderTarget* rt = static_cast<ID2D1HwndRenderTarget*>(renderTarget);
	hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &rt);
	if (hr != S_OK) return false;
	renderTarget = rt;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(dwriteFactory), reinterpret_cast<IUnknown **>(&dwriteFactory));
	if (hr != S_OK) return false;

	hr = CoCreateInstance(CLSID_WICImagingFactory, 0, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void**)&wicFactory);
	if (hr != S_OK) return false;
	
	return true;
}

bool CD2DRenderer::init(HWND windowHandle, IDXGISwapChain *swapChain)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (hr != S_OK) return false;

	IDXGISurface* dxgiSurface = nullptr;
	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiSurface));
	if (hr != S_OK) return false;

	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
	hr = factory->CreateDxgiSurfaceRenderTarget(dxgiSurface, &props, &renderTarget);

	safeRelease(dxgiSurface);
	if (hr != S_OK) return false;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(dwriteFactory), reinterpret_cast<IUnknown **>(&dwriteFactory));
	if (hr != S_OK) return false;

	hr = CoCreateInstance(CLSID_WICImagingFactory, 0, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void**)&wicFactory);
	if (hr != S_OK) return false;

	return true;
}

void CD2DRenderer::clearScreen(const float &r, const float &g, const float &b) const
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void CD2DRenderer::drawCircle(const float &x, const float &y, const float &radius, const float &thickness, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brushes[brushName], thickness);
	else
		renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), currentBrush, thickness);
}

void CD2DRenderer::fillCircle(const float &x, const float &y, const float &radius, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brushes[brushName]);
	else
		renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), currentBrush);
}

void CD2DRenderer::drawEllipse(const float &x, const float &y, const float &radiusX, const float &radiusY, const float &thickness, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY), brushes[brushName], thickness);
	else
		renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY), currentBrush, thickness);
}

void CD2DRenderer::fillEllipse(const float &x, const float &y, const float &radiusX, const float &radiusY, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY), brushes[brushName]);
	else
		renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY), currentBrush);
}

void CD2DRenderer::drawLine(const float &x, const float &y, const float &x2, const float &y2, const float &thickness, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x2, y2), brushes[brushName], thickness);
	else
		renderTarget->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x2, y2), currentBrush, thickness);
}

void CD2DRenderer::drawRect(const float &x, const float &y, const float &w, const float &h, const float &thickness, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->DrawRectangle(D2D1::RectF(x, y, x + w, y + h), brushes[brushName], thickness);
	else
		renderTarget->DrawRectangle(D2D1::RectF(x, y, x + w, y + h), currentBrush, thickness);
}

void CD2DRenderer::fillRect(const float &x, const float &y, const float &w, const float &h, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->FillRectangle(D2D1::RectF(x, y, x + w, y + h), brushes[brushName]);
	else
		renderTarget->FillRectangle(D2D1::RectF(x, y, x + w, y + h), currentBrush);
}

void CD2DRenderer::drawRoundedRect(const float &x, const float &y, const float &w, const float &h, const float &radiusX, const float &radiusY, const float &thickness, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x, y, x + w, y + h), radiusX, radiusY), brushes[brushName], thickness);
	else
		renderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x, y, x + w, y + h), radiusX, radiusY), currentBrush, thickness);
}
void CD2DRenderer::fillRoundedRect(const float &x, const float &y, const float &w, const float &h, const float &radiusX, const float &radiusY, const std::string &brushName)
{
	if (!brushName.empty())
		renderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x, y, x + w, y + h), radiusX, radiusY), brushes[brushName]);
	else
		renderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x, y, x + w, y + h), radiusX, radiusY), currentBrush);
}

void CD2DRenderer::drawText(const std::wstring &text, const float &x, const float &y, const float &w, const float &h, const std::string &brushName, const std::string &fontName)
{
	if (!brushName.empty()) {
		if (!fontName.empty())
			renderTarget->DrawText(text.c_str(), text.size(), fonts[fontName], D2D1::RectF(x, y, x + w, y + h), brushes[brushName]);
		else
			renderTarget->DrawText(text.c_str(), text.size(), currentFont, D2D1::RectF(x, y, x + w, y + h), brushes[brushName]);
	}
	else {
		if (!fontName.empty())
			renderTarget->DrawText(text.c_str(), text.size(), fonts[fontName], D2D1::RectF(x, y, x + w, y + h), currentBrush);
		else
			renderTarget->DrawText(text.c_str(), text.size(), currentFont, D2D1::RectF(x, y, x + w, y + h), currentBrush);
	}
}

void CD2DRenderer::drawBitmap(const std::string &bitmapName, const float &x, const float &y)
{
	ID2D1Bitmap *bmp = bitmaps[bitmapName];
	renderTarget->DrawBitmap(bmp, D2D1::RectF(x, y, x + bmp->GetSize().width, y + bmp->GetSize().height), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));

}

void CD2DRenderer::setBrush(const std::string &brushName)
{
	currentBrush = brushes[brushName];
}

void CD2DRenderer::addBrush(ID2D1Brush *brush, const std::string &brushName)
{
	brushes[brushName] = brush;
}

void CD2DRenderer::addSolidBrush(const std::string &brushName, const D2D1::ColorF &color)
{
	ID2D1SolidColorBrush *brush = nullptr;
	renderTarget->CreateSolidColorBrush(color, &brush);
	addBrush(brush, brushName);
}

void CD2DRenderer::removeBrush(const std::string &brushName)
{
	safeRelease(brushes[brushName]);
	brushes.erase(brushName);
}

void CD2DRenderer::setFont(const std::string &fontName)
{
	currentFont = fonts[fontName];
}

void CD2DRenderer::addFont(IDWriteTextFormat *font, const std::string &fontName)
{
	fonts[fontName] = font;
}

void CD2DRenderer::addFont(const std::string &fontID, const std::wstring &fontName, const float &size, const bool &centerHorizontally, const bool &centerVertically)
{
	static const wchar_t* fname = fontName.c_str();
	IDWriteTextFormat *textFormat = nullptr;
	dwriteFactory->CreateTextFormat(fname, 0, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &textFormat);
	if (centerHorizontally)
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	if (centerVertically)
		textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	addFont(textFormat, fontID);
}

void CD2DRenderer::removeFont(const std::string &fontName)
{
	safeRelease(fonts[fontName]);
	fonts.erase(fontName);
}

void CD2DRenderer::addBitmap(const std::string &bitmapName, const std::wstring &path)
{
	bitmaps[bitmapName] = loadBitmapFromFile(path);
}

void CD2DRenderer::removeBitmap(const std::string &bitmapName)
{
	safeRelease(bitmaps[bitmapName]);
	bitmaps.erase(bitmapName);
}

ID2D1Bitmap *CD2DRenderer::loadBitmapFromFile(const std::wstring &path)
{
	IWICBitmapDecoder *wicDecoder = nullptr;
	HRESULT hr = wicFactory->CreateDecoderFromFilename(path.c_str(), 0, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &wicDecoder);
	if (hr != S_OK) {
		throw std::exception("Error creating decoder. Check the file path.");
	}

	IWICBitmapFrameDecode *wicFrame = nullptr;
	hr = wicDecoder->GetFrame(0, &wicFrame);
	if (hr != S_OK) {
		throw std::exception("Error getting frame.");
	}

	IWICFormatConverter *wicConverter = nullptr;
	hr = wicFactory->CreateFormatConverter(&wicConverter);
	if (hr != S_OK) {
		throw std::exception("Error creating format converter.");
	}

	hr = wicConverter->Initialize(wicFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, 0, 0.0f, WICBitmapPaletteTypeCustom);
	if (hr != S_OK) {
		throw std::exception("Error initializing converter.");
	}

	ID2D1Bitmap *bmp = nullptr;
	hr = renderTarget->CreateBitmapFromWicBitmap(wicConverter, 0, &bmp);
	if (hr != S_OK) {
		throw std::exception("Error creating bitmap from WicBitmap.");
	}

	safeRelease(wicDecoder);
	safeRelease(wicFrame);
	safeRelease(wicConverter);

	return bmp;
}