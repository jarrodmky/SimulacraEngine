//===========================================================================
// Filename:	Application.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Application.h"

using namespace Core;

//===========================================================================
// Class Definitions
//===========================================================================

Application::Application()
: m_Running(true)
, m_Instance(nullptr)
, m_Window(nullptr)
, m_AppName()
{}

//---------------------------------------------------------------------------

Application::~Application() {}

//---------------------------------------------------------------------------

bool Application::Initialize(HINSTANCE p_Instance, LPCSTR p_AppName, u32 p_Width, u32 p_Height)
{
	m_Instance = p_Instance;
	m_AppName = p_AppName;

	OnInitialize(p_Width, p_Height);

	m_Running = true;

	return true;
}

//---------------------------------------------------------------------------

void Application::Terminate()
{
	OnTerminate();

	m_Running = false;
}

//---------------------------------------------------------------------------

void Application::HookupWindow(HWND p_Hwnd)
{
	m_Window = p_Hwnd;
}

//---------------------------------------------------------------------------

void Application::UnhookWindow()
{
	m_Window = nullptr;
}

//---------------------------------------------------------------------------

void Application::Update()
{
	OnUpdate();
}