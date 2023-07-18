#include "StdAfx.h"
#include "Application.h"

Duilib::CApplication* Duilib::CApplication::Get()
{
	static CApplication app;
	return &app;
}


bool Duilib::CApplication::Init()
{
	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	CPaintManagerUI::SetInstance(hInstance);
	HRESULT hr = ::OleInitialize(NULL);
	if (FAILED(hr))
	{
		return false;
	}
	hr = ::CoInitialize(NULL);
	if (FAILED(hr))
	{
		::OleUninitialize();
		return false;
	}
	return true;
}

int Duilib::CApplication::Run()
{
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Destroy();
	return (int)msg.wParam;
}


void Duilib::CApplication::Destroy()
{
	::OleUninitialize();
	::CoUninitialize();
}

Duilib::CApplication::CApplication()
{
	
}

Duilib::CApplication::~CApplication()
{

}
