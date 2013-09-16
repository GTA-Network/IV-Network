#include "CCore.h"

class CGUIView
{
public:
		CGUIView(Gwen::Renderer::DirectX9* pRenderer);
		~CGUIView();
		
		void Render();
		bool ProcessInput(MSG msg);
		
		void SetScreenSize(int iWidth, int iHeight);
		Gwen::Controls::Canvas* GetCanvas() { return m_pCanvas; }
private:
		Gwen::Renderer::DirectX9* m_pRenderer;
		Gwen::Skin::Simple skin;
		Gwen::Controls::Canvas* m_pCanvas;
		Gwen::Input::Windows* m_pInput;
};