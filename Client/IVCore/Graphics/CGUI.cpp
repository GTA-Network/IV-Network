//========== IV:Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CGUI.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CCore.h"

extern CCore* g_pCore;

#include <Shlobj.h>

CGUI::CGUI(IDirect3DDevice9* pDevice) :
	m_pD3DDevice(pDevice),
	m_pRenderer(NULL),
	m_pSystem(NULL),
	m_pCursor(NULL),
	m_pWindowManager(NULL),
	m_pDefaultWindow(NULL),
	m_pInput(NULL),
	m_pInputMouse(NULL),
	m_bInitialized(false),
	m_dwDoubleClickTime(GetDoubleClickTime()),
	m_iCurrentId(0),
	m_uiCurrentName(0)
{

	memset(&m_messageBox, 0, sizeof(m_messageBox));
	memset(dwLastClickTime, 0, sizeof(DWORD) * 8);
	memset(byteButtonWasClicked, 0, sizeof(BYTE) * 8);
	memset(byteButtonClicked, 0, sizeof(BYTE) * 8);
	memset(&m_rCursorPosition, 0, sizeof(RECT));
	memset(&m_clickPosition, 0, sizeof(POINT));
}

CGUI::~CGUI()
{

}

bool CGUI::Initialize()
{
	if (!m_bInitialized)
	{
		m_pRenderer = &CEGUI::Direct3D9Renderer::create(m_pD3DDevice);

		m_pSystem = &CEGUI::System::create(*m_pRenderer);

		CEGUI::Logger * pLogger = CEGUI::Logger::getSingletonPtr();

		pLogger->setLogFilename(SharedUtility::GetAbsolutePath("CEGUI.log").Get());

		m_pWindowManager = CEGUI::WindowManager::getSingletonPtr();

		m_pFontManager = CEGUI::FontManager::getSingletonPtr();

		CEGUI::DefaultResourceProvider * rp = (CEGUI::DefaultResourceProvider *)m_pSystem->getResourceProvider();

		// For each resource type, set a resource group directory
		rp->setResourceGroupDirectory("schemes", SharedUtility::GetAbsolutePath("CEGUI/schemes/").Get());
		rp->setResourceGroupDirectory("imagesets", SharedUtility::GetAbsolutePath("CEGUI/imagesets/").Get());
		rp->setResourceGroupDirectory("fonts", SharedUtility::GetAbsolutePath("CEGUI/fonts/").Get());
		rp->setResourceGroupDirectory("layouts", SharedUtility::GetAbsolutePath("CEGUI/layouts/").Get());
		rp->setResourceGroupDirectory("looknfeels", SharedUtility::GetAbsolutePath("CEGUI/looknfeel/").Get());
		rp->setResourceGroupDirectory("schemas", SharedUtility::GetAbsolutePath("CEGUI/xml_schemas/").Get());
		rp->setResourceGroupDirectory("resources", SharedUtility::GetAbsolutePath("clientfiles/resources/").Get());


		// Register the windows fonts directory as a resource group directory
		char strFontPath[MAX_PATH];

		if (SHGetSpecialFolderPath(NULL, strFontPath, CSIDL_FONTS, FALSE))
			rp->setResourceGroupDirectory("winfonts", strFontPath);


		// Set the default resource groups to be used
		CEGUI::Imageset::setDefaultResourceGroup("imagesets");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		m_pWindowManager->setDefaultResourceGroup("layouts");


		// Setup default group for validation schemas
		CEGUI::XMLParser * parser = m_pSystem->getXMLParser();

		if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
			parser->setProperty("SchemaDefaultResourceGroup", "schemas");

		// Clearing this queue actually makes sure it's created
		//m_pRenderer->getDefaultRenderingRoot().clearGeometry(CEGUI::RQ_OVERLAY);

		// Load the gui scheme
		m_pScheme = &CEGUI::SchemeManager::getSingleton().create(STYLE_SCHEME);

		// Set the mouse cursor
		m_pSystem->setDefaultMouseCursor(STYLE_IMAGES, "MouseArrow");


		// Get a pointer to the gui cursor
		m_pCursor = CEGUI::MouseCursor::getSingletonPtr();

		// Hide the mouse cursor
		m_pCursor->setVisible(false);

		// Create the default gui window
		m_pDefaultWindow = (CEGUI::DefaultWindow *)m_pWindowManager->createWindow("DefaultWindow", GetUniqueName());

		// Set the default gui window size
		m_pDefaultWindow->setSize(CEGUI::UVector2(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));

		// Set the default gui window alpha
		m_pDefaultWindow->setAlpha(1.0f);

		// Subscribe to our global key down event
		CEGUI::GlobalEventSet::getSingletonPtr()->subscribeEvent(CEGUI::Window::EventNamespace + "/" + CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&CGUI::OnGUIKeyDown, this));

		// Set the default gui window as the gui sheet
		m_pSystem->setGUISheet(m_pDefaultWindow);

		// Setup text drawing geometry buffer
		m_pTextDrawingGeometryBuffer = &m_pRenderer->createGeometryBuffer();
		m_pTextDrawingGeometryBuffer->setClippingRegion(CEGUI::Rect(CEGUI::Vector2(0, 0), m_pRenderer->getDisplaySize()));

		// Set the default GUI font
		m_pSystem->setDefaultFont(GetFont(CVAR_GET_STRING("chatfont").Get()));

		// Create the input
		if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8A, (LPVOID *) &m_pInput, nullptr)))
			return false;

		// Create the input device
		if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pInputMouse, nullptr)))
			return false;

		// Set the input device as a mouse
		if (FAILED(m_pInputMouse->SetDataFormat(&c_dfDIMouse2)))
			return false;

		// Set the input device to non exclusive
		if (FAILED(m_pInputMouse->SetCooperativeLevel(*(HWND *) COffsets::VAR_HWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
			return false;

		// Acquire the input device
		if (FAILED(m_pInputMouse->Acquire()))
			return false;

		// Get the input device info
		DIDEVCAPS MouseCapabilities;
		MouseCapabilities.dwSize = sizeof(MouseCapabilities);

		if (FAILED(m_pInputMouse->GetCapabilities(&MouseCapabilities)))
			return false;

		m_dwInputAxes = MouseCapabilities.dwAxes;
		m_dwInputButtons = MouseCapabilities.dwButtons;

		// Initialize the mouse button info
		for (BYTE i = 0; i < 8; i++)
		{
			dwLastClickTime[i] = 0;
			byteButtonWasClicked[i] = 0;
			byteButtonClicked[i] = 0;
		}

		m_bInitialized = true;

		return true;
	}
	return false;
}

unsigned int CGUI::GetDisplayWidth()
{
	// If we have a renderer get the display width
	if (m_pRenderer)
		return (unsigned int) m_pRenderer->getDisplaySize().d_width;

	return 0;
}

unsigned int CGUI::GetDisplayHeight()
{
	// If we have a renderer get the display height
	if (m_pRenderer)
		return (unsigned int) m_pRenderer->getDisplaySize().d_height;

	return 0;
}

void CGUI::Render()
{
	// Make sure we are initialized
	if (m_bInitialized)
	{

		// Render our GUI
		if (m_pSystem)
			m_pSystem->renderGUI();

		//m_pCursor->setVisible(true);

		// Process our mouse events
		if (g_pCore->GetHWNDFocused())
		{
			if (!m_pInput || !m_pInputMouse)
				return;

			if (m_pCursor->isVisible())
			{
				// If we have lost the input device re-acquire it
				if (m_pInputMouse->GetDeviceState(sizeof(m_MouseState), (LPVOID) &m_MouseState) == DIERR_INPUTLOST)
				{
					if (FAILED(m_pInputMouse->Acquire()))
						return;
				}

				// Handle mouse position changes
				m_rCursorPosition.left += m_MouseState.lX;

				if (m_rCursorPosition.left > (long) GetDisplayWidth())
					m_rCursorPosition.left = (long) GetDisplayWidth();
				else if (m_rCursorPosition.left < 0)
					m_rCursorPosition.left = 0;

				m_rCursorPosition.top += m_MouseState.lY;

				if (m_rCursorPosition.top >(long)GetDisplayHeight())
					m_rCursorPosition.top = (long) GetDisplayHeight();
				else if (m_rCursorPosition.top < 0)
					m_rCursorPosition.top = 0;

				m_pSystem->injectMousePosition((float) m_rCursorPosition.left, (float) m_rCursorPosition.top);

				// If the window has focus sync the windows cursor position with 
				// the direct input cursor position
				if (g_pCore->GetHWNDFocused())
					SetCursorPos(m_rCursorPosition.left, m_rCursorPosition.top);

				// Check the mouse wheel for changes
				if (m_MouseState.lZ != 0)
					m_pSystem->injectMouseWheelChange((float) m_MouseState.lZ);

				// Check the mouse buttons for changes
				// TODO: Fix double click detection
				// TODO: First click after a double click should be a single click
				for (BYTE i = 0; i < 8; i++)
				{
					if (m_MouseState.rgbButtons[i] & 0x80)
					{
						if (!byteButtonClicked[i])
						{
							bool bDoubleClick = false;

							if (dwLastClickTime[i])
							{
								if ((SharedUtility::GetTime() - dwLastClickTime[i]) < m_dwDoubleClickTime)
								{
									if (m_clickPosition.x == m_rCursorPosition.left && m_clickPosition.y == m_rCursorPosition.top)
									{
										if (i < 3)
										{
											m_pSystem->injectMouseButtonDoubleClick((CEGUI::MouseButton)i);
											bDoubleClick = true;
										}
									}
								}
							}

							if (!bDoubleClick)
							{
								if (i < 3)
									m_pSystem->injectMouseButtonDown((CEGUI::MouseButton)i);
							}

							dwLastClickTime[i] = SharedUtility::GetTime();
							byteButtonClicked[i] = 1;
						}
					}
					else
					{
						if (byteButtonClicked[i])
						{
							if (i < 3)
								m_pSystem->injectMouseButtonUp((CEGUI::MouseButton)i);
						}

						byteButtonClicked[i] = 0;
					}
				}
			}
		}

	}
}

void CGUI::OnLostDevice()
{
	// Make sure we are initialized
	if (m_bInitialized)
	{
		// Notify our GUI renderer that the device has been lost
		if (m_pRenderer)
			m_pRenderer->preD3DReset();
	}
}

void CGUI::OnResetDevice()
{
	// Make sure we are initialized
	if (m_bInitialized)
	{
		// Notify our GUI renderer that the device has been reset
		if (m_pRenderer)
			m_pRenderer->postD3DReset();
	}
}

char* CGUIWindow::getText()
{
	CEGUI::String str = CEGUI::Window::getText();
	int len = str.length();

	if (len == 0)
		return "";

	char *Ansi = new char[str.length() + 1];
	wchar_t *Unicode = new wchar_t[str.length() + 1];

	for (size_t i = 0; i < str.size(); i++)
		Unicode[i] = str[i];

	WideCharToMultiByte(CP_ACP, NULL, Unicode, -1, Ansi, len, NULL, NULL);
	Ansi[str.length()] = '\0';

	delete [] Unicode;

	return Ansi;
}

bool CGUI::OnGUIKeyDown(const CEGUI::EventArgs &eventArgs)
{
	// Cast the argument to a key event args structure
	const CEGUI::KeyEventArgs &keyEventArgs = (const CEGUI::KeyEventArgs &)eventArgs;

	// Check if the left or right control key is held down
	if (keyEventArgs.sysKeys & CEGUI::Control)
	{
		// Check if its the a key that was pressed
		if (keyEventArgs.scancode == CEGUI::Key::A)
		{
			// Make sure its an edit box that is selected
			if (keyEventArgs.window->getType() == STYLE_PREFIX "/Editbox")
			{
				// Get the edit box pointer
				CEGUI::Editbox * pEditBox = (CEGUI::Editbox *)keyEventArgs.window;

				// Set the selection start to 0 and end to the edit box text length
				pEditBox->setSelection(0, pEditBox->getText().size());
			}
		}
		else if (keyEventArgs.scancode == CEGUI::Key::C || keyEventArgs.scancode == CEGUI::Key::X)
		{
			// Make sure its an edit box that is selected
			if (keyEventArgs.window->getType() == STYLE_PREFIX "/Editbox")
			{
				// Get the edit box pointer
				if (keyEventArgs.window->getType() == STYLE_PREFIX "/Editbox")
				{
					CEGUI::Editbox * pEditBox = (CEGUI::Editbox *)keyEventArgs.window;
					// Get the edit box selection length
					size_t sSelectionLength = pEditBox->getSelectionLength();
					if (sSelectionLength > 0)
					{
						// Get the edit box selection start index
						size_t sSelectionStartIndex = pEditBox->getSelectionStartIndex();

						// Get the edit box selection end index
						size_t sSelectionEndIndex = (sSelectionStartIndex + sSelectionLength);

						// Get the edit box text
						CEGUI::String sEditBoxText = pEditBox->getText();

						// Get the text we wish to copy from the edit box text
						CEGUI::String sSelectionText = sEditBoxText.substr(sSelectionStartIndex, sSelectionEndIndex);

						// Set the clipboard text
						SharedUtility::SetClipboardText(sSelectionText.c_str(), (sSelectionText.length() + 1));

						// If its the control + x key cut the selection from the edit box text
						if (keyEventArgs.scancode == CEGUI::Key::X)
						{
							// Cut the text from the edit box text
							sEditBoxText.replace(sSelectionStartIndex, sSelectionEndIndex, "");

							// Set the edit box text to the new cut text
							pEditBox->setText(sEditBoxText);
						}
					}
				}
			}
		}
		else if (keyEventArgs.scancode == CEGUI::Key::V)
		{
			// Make sure its an edit box that is selected
			if (keyEventArgs.window->getType() == STYLE_PREFIX "/Editbox")
			{
				// If its an edit box
				if (keyEventArgs.window->getType() == STYLE_PREFIX "/Editbox")
				{
					// Get the edit box pointer
					CEGUI::Editbox * pEditBox = (CEGUI::Editbox *)keyEventArgs.window;

					// Get the edit box selection length
					size_t sSelectionLength = pEditBox->getSelectionLength();

					// Get the edit box selection start index
					size_t sSelectionStartIndex = pEditBox->getSelectionStartIndex();

					// Get the edit box text
					CEGUI::String sEditBoxText = pEditBox->getText();

					// Get the clipboard text
					const char * szClipboardText = SharedUtility::GetClipboardText();

					// Do we have any clipboard text?
					if (szClipboardText)
					{
						// Get the caret index
						size_t sCaretIndex = pEditBox->getCaratIndex();

						// Add the clipboard text length to the caret index
						sCaretIndex += strlen(szClipboardText);

						// If we don't have a selection just insert the text
						if (sSelectionLength == 0)
							sEditBoxText.insert(sSelectionStartIndex, szClipboardText);
						// If we do have a selection overwrite the selected text
						else
							sEditBoxText.replace(sSelectionStartIndex, sSelectionLength, szClipboardText);

						// Set the edit box text to the string with the pasted text
						pEditBox->setText(sEditBoxText);

						// Set the edit box caret index to the new index after the pasted text
						pEditBox->setCaratIndex(sCaretIndex);
					}
				}
			}
		}
	}

	return false;
}

const char * CGUI::GetUniqueName()
{
	static char szName[20];
	sprintf(szName, "window%d", m_uiCurrentName);
	m_uiCurrentName++;
	return szName;
}

CEGUI::Font * CGUI::GetFont(CString strFont, unsigned int uiSize, bool bScaled)
{
	if (m_bInitialized && strFont.IsNotEmpty())
	{
		// Get the font internal name
		CString strInternalFont("%s#%d#%d", strFont.ToLower().Get(), uiSize, bScaled);

		// Is the font already loaded?
		if (m_pFontManager->isDefined(strInternalFont.Get()))
			return &m_pFontManager->get(strInternalFont.Get());

		// Get the font name
		CString strName("%s.ttf", strFont.ToLower().Get());

		// Attempt to create the front from the fonts directory
		try {
			return &CEGUI::FontManager::getSingleton().createFreeTypeFont(strInternalFont.Get(), (float) uiSize, true, strName.Get(), "", bScaled);
		}
		catch (CEGUI::Exception e) {}

		// Attempt to create the font from the client resource directory
		try {
			return &CEGUI::FontManager::getSingleton().createFreeTypeFont(strInternalFont.Get(), (float) uiSize, true, strName.Get(), "resources", bScaled);
		}
		catch (CEGUI::Exception e) {}

		// Attempt to create the font from the windows fonts directory
		try {
			return &CEGUI::FontManager::getSingleton().createFreeTypeFont(strInternalFont.Get(), (float) uiSize, true, strName.Get(), "winfonts", bScaled);
		}
		catch (CEGUI::Exception e) {}
	}

	// Font does not exist and font creation failed
	return NULL;
}

void CGUI::SetCursorVisible(bool bVisible)
{
	// Are we initalized?
	if (m_bInitialized)
	{
		m_pCursor->setVisible(bVisible);
	}
}

void CGUI::ShowMessageBox(const CEGUI::String &sText, const CEGUI::String &sTitle, eGUIMessageBoxType style, GUIMessageBoxHandler_t pfnHandler)
{
	// Are we initialized?
	if (m_bInitialized)
	{
		// If we have any current message box, let's hide it
		HideMessageBox();

		// If any other message box exist, destroy it
		if (m_messageBox.pWindow)
		{
			m_messageBox.pWindow->destroy();
		}

		// Now lets create our message box

		m_messageBox.pWindow = CreateGUIFrameWindow();
		((CEGUI::FrameWindow *)m_messageBox.pWindow)->setCloseButtonEnabled(false);

		m_messageBox.pWindow->setText(sTitle);
		m_messageBox.pWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.2f, 0)));
		m_messageBox.pWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f, 0), CEGUI::UDim(0.4f, 0)));
		m_messageBox.pWindow->setAlwaysOnTop(true);
		m_messageBox.pWindow->setVisible(true);

		// Create the message box window text
		m_messageBox.pText = CreateGUIStaticText(m_messageBox.pWindow);
		m_messageBox.pText->setText(sText);
		m_messageBox.pText->setSize(CEGUI::UVector2(CEGUI::UDim(0.8f, 0), CEGUI::UDim(0.6f, 0)));
		m_messageBox.pText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f, 0), CEGUI::UDim(0.01f, 0)));
		m_messageBox.pText->setProperty("FrameEnabled", "false");
		m_messageBox.pText->setProperty("BackgroundEnabled", "false");
		m_messageBox.pText->setVisible(true);
		m_messageBox.pText->setFont(GetFont("arial", 15));

		// Create the message box window button(s)
		if (style == GUI_MESSAGEBOXTYPE_OK)
		{
			// Create the 'Ok' button
			m_messageBox.pButtons[0] = CreateGUIButton(m_messageBox.pWindow);
			m_messageBox.pButtons[0]->setText("Ok");
			m_messageBox.pButtons[0]->setSize(CEGUI::UVector2(CEGUI::UDim(0.4f, 0), CEGUI::UDim(0.15f, 0)));
			m_messageBox.pButtons[0]->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.75f, 0)));
			m_messageBox.pButtons[0]->setVisible(true);
			m_messageBox.pButtons[0]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGUI::OnMessageBoxClick, this));
		}
		else if (style == GUI_MESSAGEBOXTYPE_YESNO || style == GUI_MESSAGEBOXTYPE_YESNOCANCEL)
		{
			// Create the 'Yes' button
			m_messageBox.pButtons[0] = CreateGUIButton(m_messageBox.pWindow);
			m_messageBox.pButtons[0]->setText("Yes");

			if (style == GUI_MESSAGEBOXTYPE_YESNO)
			{
				m_messageBox.pButtons[0]->setSize(CEGUI::UVector2(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.15f, 0)));
				m_messageBox.pButtons[0]->setPosition(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.75f, 0)));
			}
			else if (style == GUI_MESSAGEBOXTYPE_YESNOCANCEL)
			{
				m_messageBox.pButtons[0]->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.15f, 0)));
				m_messageBox.pButtons[0]->setPosition(CEGUI::UVector2(CEGUI::UDim(0.15f, 0), CEGUI::UDim(0.75f, 0)));
			}

			m_messageBox.pButtons[0]->setVisible(true);
			m_messageBox.pButtons[0]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGUI::OnMessageBoxClick, this));

			// Create the 'No' button
			m_messageBox.pButtons[1] = CreateGUIButton(m_messageBox.pWindow);
			m_messageBox.pButtons[1]->setText("No");

			if (style == GUI_MESSAGEBOXTYPE_YESNO)
			{
				m_messageBox.pButtons[1]->setSize(CEGUI::UVector2(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.15f, 0)));
				m_messageBox.pButtons[1]->setPosition(CEGUI::UVector2(CEGUI::UDim(0.55f, 0), CEGUI::UDim(0.75f, 0)));
			}
			else if (style == GUI_MESSAGEBOXTYPE_YESNOCANCEL)
			{
				m_messageBox.pButtons[1]->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.15f, 0)));
				m_messageBox.pButtons[1]->setPosition(CEGUI::UVector2(CEGUI::UDim(0.45f, 0), CEGUI::UDim(0.75f, 0)));
			}

			m_messageBox.pButtons[1]->setVisible(true);
			m_messageBox.pButtons[1]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGUI::OnMessageBoxClick, this));

			if (style == GUI_MESSAGEBOXTYPE_YESNOCANCEL)
			{
				// Create the 'Cancel' button
				m_messageBox.pButtons[2] = CreateGUIButton(m_messageBox.pWindow);
				m_messageBox.pButtons[2]->setText("Cancel");
				m_messageBox.pButtons[2]->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.15f, 0)));
				m_messageBox.pButtons[2]->setPosition(CEGUI::UVector2(CEGUI::UDim(0.75f, 0), CEGUI::UDim(0.75f, 0)));
				m_messageBox.pButtons[2]->setVisible(true);
				m_messageBox.pButtons[2]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGUI::OnMessageBoxClick, this));
			}
		}

		// Set the handler
		m_messageBox.pfnHandler = pfnHandler;

		if (!m_pCursor->isVisible())
		{
			m_pCursor->setVisible(true);
		}
	}
}

void CGUI::HideMessageBox()
{
	// Are we initialized?
	if (m_bInitialized)
	{
		// Perform a loop through all the current message box buttons
		for (int i = 0; i < ARRAY_LENGTH(m_messageBox.pButtons); i++)
		{
			// Does this button exist?
			if (m_messageBox.pButtons[i])
			{
				// Remove this button
				RemoveGUIWindow(m_messageBox.pButtons[i]);
				m_messageBox.pButtons[i] = NULL;
			}
		}

		// Does the message box text exist?
		if (m_messageBox.pText)
		{
			// Remove the message box text
			RemoveGUIWindow(m_messageBox.pText);
			m_messageBox.pText = NULL;
		}

		// Does the message box window exist?
		if (m_messageBox.pWindow)
		{
			// Remove the message box window
			RemoveGUIWindow(m_messageBox.pWindow);
			m_messageBox.pWindow = NULL;
		}

		// Reset the handler
		m_messageBox.pfnHandler = NULL;
	}
}

bool CGUI::OnMessageBoxClick(const CEGUI::EventArgs &eventArgs)
{
	// Get the window
	CEGUI::Window * pWindow = ((const CEGUI::WindowEventArgs&)eventArgs).window;

	// Get the response
	eGUIMessageBoxResponse response = GUI_MESSAGEBOX_YES;

	if (pWindow == m_messageBox.pButtons[0])
	{
		response = GUI_MESSAGEBOX_YES;
	}
	else if (pWindow == m_messageBox.pButtons[1])
	{
		response = GUI_MESSAGEBOX_NO;
	}
	else if (pWindow == m_messageBox.pButtons[2])
	{
		response = GUI_MESSAGEBOX_CANCEL;
	}

	// Do we have a handler?
	if (m_messageBox.pfnHandler)
	{
		// Call the handler
		m_messageBox.pfnHandler(response);
	}

	// Hide the message box
	HideMessageBox();
	return true;
}

void CGUI::RemoveGUIWindow(CEGUI::String &sName)
{
	if (m_bInitialized)
	{
		m_pDefaultWindow->removeChildWindow(sName);
		m_pWindowManager->destroyWindow(sName);
	}
}

void CGUI::RemoveGUIWindow(CEGUI::Window * pWindow)
{
	if (m_bInitialized)
	{
		// Make sure the window exists
		if (m_pWindowManager->isWindowPresent(pWindow->getName()))
		{
			// Remove the window from the parent window
			pWindow->getParent()->removeChildWindow(pWindow);

			// Destroy the window
			m_pWindowManager->destroyWindow(pWindow);

			// Reset the window pointer
			pWindow = nullptr;
		}
	}
}

CEGUI::Window * CGUI::CreateGUIWindow(const CEGUI::String &sType, const CEGUI::String &sName, CEGUI::Window * pParentWindow)
{
	if (m_bInitialized)
	{
		CEGUI::Window * pWindow = m_pWindowManager->createWindow(sType, sName);
		if (pWindow)
		{
			CEGUI::Window * pParent = (pParentWindow == nullptr) ? m_pDefaultWindow : pParentWindow;
			pParent->addChildWindow(pWindow);
		}
		return pWindow;
	}
	return nullptr;
}

CGUIButton * CGUI::CreateGUIButton(CEGUI::String &sName, CEGUI::Window * pParentWindow)
{
	return (CGUIButton *) CreateGUIWindow(STYLE_PREFIX "/Button", sName, pParentWindow);
}

CGUIButton * CGUI::CreateGUIButton(CEGUI::Window * pParentWindow)
{
	return (CGUIButton *) CreateGUIWindow(STYLE_PREFIX "/Button", GetUniqueName(), pParentWindow);
}

CGUIStaticImage * CGUI::CreateGUIStaticImage(CEGUI::String &sName, CEGUI::Window * pParentWindow)
{
	return (CGUIStaticImage *) CreateGUIWindow(STYLE_PREFIX "/StaticImage", sName, pParentWindow);
}

CGUIStaticImage * CGUI::CreateGUIStaticImage(CEGUI::Window * pParentWindow)
{
	return (CGUIStaticImage *) CreateGUIWindow(STYLE_PREFIX "/StaticImage", GetUniqueName(), pParentWindow);
}

CGUIProgressBar * CGUI::CreateGUIProgressBar(CEGUI::String &sName, CEGUI::Window * pParentWindow)
{
	return (CGUIProgressBar *) CreateGUIWindow(STYLE_PREFIX "/ProgressBar", sName, pParentWindow);
}

CGUIProgressBar * CGUI::CreateGUIProgressBar(CEGUI::Window * pParentWindow)
{
	return (CGUIProgressBar *) CreateGUIWindow(STYLE_PREFIX "/ProgressBar", GetUniqueName(), pParentWindow);
}

CGUIStaticText * CGUI::CreateGUIStaticText(CEGUI::String &sName, CEGUI::Window * pParentWindow)
{
	return (CGUIStaticText *) CreateGUIWindow(STYLE_PREFIX "/StaticText", sName, pParentWindow);
}

CGUIStaticText * CGUI::CreateGUIStaticText(CEGUI::Window * pParentWindow)
{
	return (CGUIStaticText *) CreateGUIWindow(STYLE_PREFIX "/StaticText", GetUniqueName(), pParentWindow);
}

CGUIFrameWindow * CGUI::CreateGUIFrameWindow(CEGUI::String &sName, CEGUI::Window * pParentWindow)
{
	return (CGUIFrameWindow *) CreateGUIWindow(STYLE_PREFIX "/FrameWindow", sName, pParentWindow);
}

CGUIFrameWindow * CGUI::CreateGUIFrameWindow(CEGUI::Window * pParentWindow)
{
	return (CGUIFrameWindow *) CreateGUIWindow(STYLE_PREFIX "/FrameWindow", GetUniqueName(), pParentWindow);
}

CGUIEditBox * CGUI::CreateGUIEditBox(CEGUI::String &sName, CEGUI::Window * pParentWindow)
{
	return (CGUIEditBox *) CreateGUIWindow(STYLE_PREFIX "/Editbox", sName, pParentWindow);
}

CGUIEditBox * CGUI::CreateGUIEditBox(CEGUI::Window * pParentWindow)
{
	return (CGUIEditBox *) CreateGUIWindow(STYLE_PREFIX "/Editbox", GetUniqueName(), pParentWindow);
}

CGUIMultiColumnList * CGUI::CreateGUIMultiColumnList(CEGUI::String &sName, CEGUI::Window * pParentWindow)
{
	return (CGUIMultiColumnList *) CreateGUIWindow(STYLE_PREFIX "/MultiColumnList", sName, pParentWindow);
}

CGUIMultiColumnList * CGUI::CreateGUIMultiColumnList(CEGUI::Window * pParentWindow)
{
	return (CGUIMultiColumnList *) CreateGUIWindow(STYLE_PREFIX "/MultiColumnList", GetUniqueName(), pParentWindow);
}

CEGUI::String CGUI::AnsiToCeguiFriendlyString(const char * szAnsiString, unsigned int uiLength)
{
	wchar_t * wcUnicode = new wchar_t[uiLength + 1];
	SharedUtility::AnsiToUnicode(szAnsiString, -1, wcUnicode, uiLength);
	CEGUI::String strCegui;
	strCegui.resize(uiLength);

	for (size_t i = 0; i < uiLength; i++)
		strCegui[i] = (CEGUI::utf32)wcUnicode[i];

	delete [] wcUnicode;
	return strCegui;
}

CEGUI::String CGUI::AnsiToCeguiFriendlyString(CString strAnsiString)
{
	return AnsiToCeguiFriendlyString(strAnsiString.Get(), strAnsiString.GetLength());
}

DWORD ScanCodeToDIK(WORD wScanCode)
{
	switch (wScanCode)
	{
	case 0x41: return DIK_A;               // Control + A (Select All)
	case 0x43: return DIK_C;               // Control + C (Copy)
	case 0x58: return DIK_X;               // Control + X (Cut)
	case 0x56: return DIK_V;               // Control + V (Paste)
	case VK_TAB: return DIK_TAB;           // Tab
	case VK_HOME: return DIK_HOME;         // Home
	case VK_END: return DIK_END;           // End
	case VK_INSERT: return DIK_INSERT;     // Insert
	case VK_DELETE: return DIK_DELETE;     // Delete
	case VK_UP: return DIK_UP;             // Arrow Up
	case VK_DOWN: return DIK_DOWN;         // Arrow Down
	case VK_LEFT: return DIK_LEFT;         // Arrow Left
	case VK_RIGHT: return DIK_RIGHT;       // Arrow Right
	case VK_SHIFT: return DIK_LSHIFT;      // Shift
	case VK_LSHIFT: return DIK_LSHIFT;     // Left Shift
	case VK_RSHIFT: return DIK_RSHIFT;     // Right Shift
	case VK_BACK: return DIK_BACK;         // Backspace
	case VK_RETURN: return DIK_RETURN;     // Enter
	case VK_CONTROL: return DIK_LCONTROL;  // Control
	case VK_LCONTROL: return DIK_LCONTROL; // Left Control
	case VK_RCONTROL: return DIK_RCONTROL; // Right Control
	}

	return 0;
}

bool CGUI::HandleUserInput(UINT uMsg, WPARAM wParam)
{
	if (m_bInitialized)
	{
		// Is this a mouse event?
		switch (uMsg)
		{
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_MOUSEWHEEL:
			{
				// We handle the mouse manually with direct input
				return false;
			}
		}

		// Is it a char?
		if (uMsg == WM_CHAR)
		{
			// Temporary strings for unicode conversion
			unsigned char ucAnsi = wParam;
			WCHAR wcUnicode = 0;
			SharedUtility::AnsiToUnicode((const char *) &ucAnsi, 1, &wcUnicode, 1);

			if (m_pSystem->injectChar((CEGUI::utf32)wcUnicode))
				return true;
		}

		// Is it a key down or key up?
		else if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
		{
			// For some reason when you press ALT it sends 3 messages: (WM_KEYDOWN VK_CONTROL), (WM_KEYDOWN VK_MENU) and (WM_KEYUP VK_MENU)
			// This caused that after ALT has been pressed CEGUI thought control(VK_CONTROL) is always down
			if (wParam == VK_MENU && uMsg == WM_KEYDOWN)
				return m_pSystem->injectKeyUp(DIK_LCONTROL);

			// Convert it to a CEGUI scan code
			DWORD dwKey = ScanCodeToDIK(wParam);

			// Do we have a valid scan code?
			if (dwKey)
			{
				// Pass it to the GUI
				if (uMsg == WM_KEYDOWN)
				{
					if (m_pSystem->injectKeyDown(dwKey))
						return true;
				}
				else
				{
					if (m_pSystem->injectKeyUp(dwKey))
						return true;
				}
			}
		}
	}
	return true;
}

CGUIStaticText * CGUI::CreateButton(char * szText, CEGUI::UVector2 vecSize, CEGUI::UVector2 vecPosition)
{
	CGUIStaticText * pButton = CreateGUIStaticText();
	pButton->setText(CGUI::AnsiToCeguiFriendlyString(szText, strlen(szText)));
	pButton->setSize(vecSize);
	pButton->setPosition(vecPosition);
	pButton->setProperty("FrameEnabled", "false");
	pButton->setProperty("BackgroundEnabled", "false");
	pButton->setFont(GetFont("pricedown", 20));
	pButton->setProperty("TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF");
	return pButton;
}