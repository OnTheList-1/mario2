#include "framework.h"
#include "Setting.h"
#include "EngineBase.h"
#include "Engine.h"
#include "GameObject.h"


EngineBase::EngineBase()
{
}

EngineBase::~EngineBase()
{
}

void EngineBase::MousePosition(const int& x, const int& y)
{
	mousePosition.x = (float)x;
	mousePosition.y = (float)y;
}

void EngineBase::KeyUp(WPARAM wParam)
{
}

void EngineBase::KeyDown(WPARAM wParam)
{
}

void EngineBase::AddGameObject(GameObject* gameObject)
{
	gameObject->engine = this;
	listObject.push_back(gameObject);
}

void EngineBase::RemoveGameObject(GameObject* gameObject)
{
	listObject.remove(gameObject);
}

void EngineBase::Logic(const double& delta)
{
	for (const auto& itr : listObject)
		itr->Logic(delta);
}

void EngineBase::Draw(HDC hdc)
{
	for (const auto& itr : listObject)
		itr->Draw(hdc);
}

HBITMAP EngineBase::LoadImage(const LPCWSTR& file_path)
{
	Gdiplus::GdiplusStartupInput gpStartupInput;
	ULONG_PTR gpToken;
	GdiplusStartup(&gpToken, &gpStartupInput, NULL);
	HBITMAP result = NULL;
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(file_path, false);
	if (bitmap)
	{
		bitmap->GetHBITMAP(Gdiplus::Color(255, 255, 255), &result);
		delete bitmap;
	}
	Gdiplus::GdiplusShutdown(gpToken);
	return result;
}