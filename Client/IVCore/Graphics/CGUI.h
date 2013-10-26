//========== IV:Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CGUI.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CGUI_h
#define CGUI_h

#include <Common.h>
#include <CEGUI.h>
#include <dinput.h>
#include <RendererModules/Direct3D9/CEGUIDirect3D9Renderer.h>

#define STYLE_SCHEME "WindowsLook.scheme"
#define STYLE_PREFIX "WindowsLook"
#define STYLE_IMAGES "WindowsLook"

#define InheritedStruct(inheritFrom, structName) struct structName : inheritFrom { }

struct CGUIWindow : CEGUI::Window
{
	char* getText();
};

InheritedStruct(CGUIWindow, CGUIButton);
InheritedStruct(CGUIWindow, CGUIStaticImage);
InheritedStruct(CGUIWindow, CGUIProgressBar);
InheritedStruct(CGUIWindow, CGUIStaticText);
InheritedStruct(CGUIWindow, CGUIFrameWindow);
InheritedStruct(CGUIWindow, CGUIEditBox);
InheritedStruct(CGUIWindow, CGUIMultiColumnList);

enum eGUIMessageBoxType
{
	GUI_MESSAGEBOXTYPE_OK,
	GUI_MESSAGEBOXTYPE_YESNO,
	GUI_MESSAGEBOXTYPE_YESNOCANCEL
};

enum eGUIMessageBoxResponse
{
	GUI_MESSAGEBOX_YES,
	GUI_MESSAGEBOX_NO,
	GUI_MESSAGEBOX_CANCEL
};

typedef void (*GUIMessageBoxHandler_t)(eGUIMessageBoxResponse type);

class CGUI 
{
private:
	IDirect3DDevice9		 * m_pD3DDevice;
	// DX-based renderer
	CEGUI::Direct3D9Renderer * m_pRenderer;
	CEGUI::System            * m_pSystem;
	CEGUI::Scheme            * m_pScheme;
	CEGUI::MouseCursor       * m_pCursor;
	CEGUI::WindowManager     * m_pWindowManager;
	CEGUI::FontManager       * m_pFontManager;
	CEGUI::GeometryBuffer    * m_pTextDrawingGeometryBuffer;
	CEGUI::DefaultWindow     * m_pDefaultWindow;

	IDirectInput8            * m_pInput;
	IDirectInputDevice8      * m_pInputMouse;
	bool                       m_bInitialized;
	bool					   m_bScriptedCursorVisible;
	DWORD                      m_dwInputAxes;
	DWORD                      m_dwInputButtons;
	DIMOUSESTATE2              m_MouseState;
	DWORD                      dwLastClickTime[8];
	BYTE                       byteButtonWasClicked[8];
	BYTE                       byteButtonClicked[8];
	RECT                       m_rCursorPosition;
	int                        m_iCurrentId;
	DWORD                      m_dwDoubleClickTime;
	POINT                      m_clickPosition;
	unsigned int               m_uiCurrentName;

	int m_iScreenWidth;
	int m_iScreenHeight;

public:
	CGUI(IDirect3DDevice9* pDevice);
	~CGUI();

	void Render();
	bool Initialize();

	void            DrawText(CString sText, CEGUI::Vector2 vecPosition, CEGUI::ColourRect rColorRect = CEGUI::colour(0xFFFFFFFF), CEGUI::Font * pFont = NULL, bool bProcessFormatting = true, bool bAllowColorFormatting = true, CEGUI::Rect * rClipRect = NULL, float fSpaceExtra = 0.0f, float fXScale = 1.0f, float fYScale = 1.0f);
	void            DrawText(CString sText, CEGUI::Vector2 vecPosition, CEGUI::ColourRect rColorRect, CString sFontName, bool bProcessFormatting = true, bool bAllowColorFormatting = true, CEGUI::Rect * rClipRect = NULL, float fSpaceExtra = 0.0f, float fXScale = 1.0f, float fYScale = 1.0f);

	const char	  * GetUniqueName();
	bool			OnGUIKeyDown(const CEGUI::EventArgs &eventArgs);

	unsigned int	GetDisplayWidth();
	unsigned int	GetDisplayHeight();

	void			OnLostDevice();
	void			OnResetDevice();

	void			SetCursorVisible(bool bVisible);

	CEGUI::Direct3D9Renderer * GetRenderer() { return m_pRenderer; }
	CEGUI::System            * GetSystem() { return m_pSystem; }
	CEGUI::WindowManager     * GetWindowManager() { return m_pWindowManager; }
	CEGUI::DefaultWindow     * GetDefaultWindow() { return m_pDefaultWindow; }
	CEGUI::Font              * GetFont(CString strFont, unsigned int uiSize = 8, bool bScaled = false);

	struct
	{
		CGUIFrameWindow      * pWindow;
		CGUIStaticText       * pText;
		CGUIButton           * pButtons[3];
		GUIMessageBoxHandler_t pfnHandler;
	} m_messageBox;

	// Later on we'll need to make this a single function with seperate types
	void                       RemoveGUIWindow(CEGUI::String &sName);
	void                       RemoveGUIWindow(CEGUI::Window * pWindow);
	CEGUI::Window            * CreateGUIWindow(const CEGUI::String &sType, const CEGUI::String &sName = "", CEGUI::Window * pParentWindow = NULL);
	CGUIStaticImage          * CreateGUIStaticImage(CEGUI::String &sName, CEGUI::Window * pParentWindow = NULL);
	CGUIStaticImage          * CreateGUIStaticImage(CEGUI::Window * pParentWindow = NULL);
	CGUIButton               * CreateGUIButton(CEGUI::String &sName, CEGUI::Window * pParentWindow = NULL);
	CGUIButton               * CreateGUIButton(CEGUI::Window * pParentWindow = NULL);
	CGUIProgressBar			 * CreateGUIProgressBar(CEGUI::String &sName, CEGUI::Window * pParentWindow = NULL);
	CGUIProgressBar		     * CreateGUIProgressBar(CEGUI::Window * pParentWindow = NULL);
	CGUIStaticText           * CreateGUIStaticText(CEGUI::String &sName, CEGUI::Window * pParentWindow = NULL);
	CGUIStaticText           * CreateGUIStaticText(CEGUI::Window * pParentWindow = NULL);
	CGUIFrameWindow          * CreateGUIFrameWindow(CEGUI::String &sName, CEGUI::Window * pParentWindow = NULL);
	CGUIFrameWindow          * CreateGUIFrameWindow(CEGUI::Window * pParentWindow = NULL);
	CGUIEditBox              * CreateGUIEditBox(CEGUI::String &sName, CEGUI::Window * pParentWindow = NULL);
	CGUIEditBox              * CreateGUIEditBox(CEGUI::Window * pParentWindow = NULL);
	CGUIMultiColumnList      * CreateGUIMultiColumnList(CEGUI::String &sName, CEGUI::Window * pParentWindow = NULL);
	CGUIMultiColumnList      * CreateGUIMultiColumnList(CEGUI::Window * pParentWindow = NULL);
	CGUIStaticText			 * CreateButton(char * szText, CEGUI::UVector2 vecSize, CEGUI::UVector2 vecPosition);

	bool                       OnMessageBoxClick(const CEGUI::EventArgs& eventArgs);
	void                       ShowMessageBox(const CEGUI::String &sText, const CEGUI::String &sTitle = "", eGUIMessageBoxType style = GUI_MESSAGEBOXTYPE_OK, GUIMessageBoxHandler_t pfnHandler = NULL);
	void                       HideMessageBox();

	static CEGUI::String       AnsiToCeguiFriendlyString(const char * szAnsiString, unsigned int uiLength);
	static CEGUI::String       AnsiToCeguiFriendlyString(CString strAnsiString);

	bool                       CGUI::HandleUserInput(UINT uMsg, WPARAM wParam);
};

#endif