#include "CCore.h"

using namespace Gwen;

CGUIView::CGUIView(Renderer::DirectX9* pRenderer)
{
	m_pRenderer = pRenderer;
	
	skin.SetRender( pRenderer );
	
	m_pCanvas = new Controls::Canvas( &skin );
	m_pCanvas->SetSkin( &skin );
	
	m_pInput = new Input::Windows();
	m_pInput->Initialize( m_pCanvas );
}

CGUIView::~CGUIView()
{
	SAFE_DELETE(m_pInput);
	SAFE_DELETE(m_pCanvas);
}

void CGUIView::Render()
{
	m_pCanvas->RenderCanvas();
}

bool CGUIView::ProcessInput(MSG msg)
{
	bool b = m_pInput->ProcessMessage(msg);
	if(b)
			CLogFile::Printf("Parsing message %d", msg.message);
	return b;
}

void CGUIView::SetScreenSize(int iWidth, int iHeight)
{
	m_pCanvas->SetSize(iWidth, iHeight);
}
	
			