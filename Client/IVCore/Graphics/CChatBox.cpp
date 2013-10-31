
#include "CChatBox.h"

CChatBox::CChatBox(CGUI * pGUI)
: m_pGUI(pGUI)
{


}

CChatBox::~CChatBox()
{

}


bool CChatBox::Initialize()
{
	m_pChatWindow = m_pGUI->CreateGUIWindow(STYLE_PREFIX "/FrameWindow", "ChatBox", 0);
	m_pChatWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 10), CEGUI::UDim(0, 10)));
	m_pChatWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0, 510), CEGUI::UDim(0, 480)));

	m_pInputBox = (CEGUI::Editbox*)m_pGUI->CreateGUIEditBox(m_pChatWindow);
	m_pChatOutputWindow = (CEGUI::Listbox*)m_pGUI->CreateGUIWindow(STYLE_PREFIX "/Listbox", "ChatOutput", m_pChatWindow);
	m_pChatOutputWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
	m_pChatOutputWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0, 500), CEGUI::UDim(0, 430.0f)));

	
	m_pInputBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 5.0f), CEGUI::UDim(0.0f, 435.0f)));
	m_pInputBox->setSize(CEGUI::UVector2(CEGUI::UDim(0, 480.0f), CEGUI::UDim(0, 25.0f)));
	m_pInputBox->setText("");

	m_pInputBox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&CChatBox::Event_KeyPressed, this));
	m_pInputBox->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&CChatBox::Event_EditTextAccepted, this));

	m_pChatHistory = new CChatHistory();

	return true;
}


CString CChatBox::GetInputText()
{
	if (m_pInputBox)
	{
		return m_pInputBox->getText().c_str();
	}

	return "";
}

bool CChatBox::Event_KeyPressed(const CEGUI::EventArgs& e)
{
	const char* cmd = 0;

	const CEGUI::KeyEventArgs& keyArgs = static_cast<const CEGUI::KeyEventArgs&>(e);

	// handle in this special way the Up/Down arrow keys, to
	// implement the chat history
	switch (keyArgs.scancode)
	{
	case CEGUI::Key::ArrowUp:
		cmd = m_pChatHistory->GetPrev();
		if (cmd)
			m_pInputBox->setText(cmd);
		break;
	case CEGUI::Key::ArrowDown:
		cmd = m_pChatHistory->GetNext();
		if (cmd)
			m_pInputBox->setText(cmd);
		break;
	default:
		return false;
	}

	return true;
}

bool CChatBox::Event_EditTextAccepted(const CEGUI::EventArgs& e)
{
	// add line into the history and clean the entrybox
	m_pChatOutputWindow->addItem(new CEGUI::ListboxTextItem(m_pInputBox->getText()));
	m_pChatHistory->Add(m_pInputBox->getText().c_str());
	m_pInputBox->setText("");
	Disable();
	return true;
}

void CChatBox::SetVisible(bool bVisible)
{
	if (bVisible)
	{
		m_pChatWindow->deactivate();
		m_pChatWindow->disable();
		m_pChatWindow->setVisible(bVisible);
	}
	else
	{
		m_pChatWindow->activate();
		m_pChatWindow->enable();
		m_pChatWindow->setVisible(bVisible);
	}
	m_bVisible = bVisible;
}

bool CChatBox::IsEnabled()
{
	return m_pInputBox->isDisabled();
}

void CChatBox::Enable()
{
	m_pInputBox->deactivate();
	m_pInputBox->disable();
}

void CChatBox::Disable()
{
	m_pInputBox->enable();
	m_pInputBox->activate();
}