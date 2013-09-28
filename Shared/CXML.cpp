//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CXML.cpp
// Project: Shared
// Author(s): Einstein
//            jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CXML.h"

CXML::CXML()
{
	m_node = NULL;
}

CXML::~CXML()
{

}

bool CXML::load(CString strFileName)
{
	m_node = NULL;

	if(!m_document.LoadFile(strFileName.C_String()))
		return false;

	m_document.SetTabSize(4);
	m_node = m_document.RootElement();
	return true;
}

bool CXML::save()
{
	return m_document.SaveFile();
}

void CXML::setTabSize(int size)
{
	m_document.SetTabSize(size);
}

const char * CXML::getAttribute(const char * attributeName)
{
	if(m_node && !isComment())
	{
		return m_node->Attribute(attributeName);
	}

	return NULL;
}

void CXML::removeAttribute(const char * attributeName)
{
	if(m_node && !isComment())
	{
		m_node->RemoveAttribute(attributeName);
	}
}

void CXML::setAttribute(const char * attributeName, const char * value)
{
	if(m_node && !isComment())
	{
		m_node->SetAttribute(attributeName, value);
	}
}

const char * CXML::nodeName()
{
	if(m_node)
	{
		return m_node->Value();
	}

	return NULL;
}

void CXML::nodeSetName(const char * content)
{
	if(m_node)
	{
		m_node->SetValue(content);
	}
}

const char * CXML::nodeContent()
{
	if(m_node && !isComment())
	{
		return m_node->GetText();
	}

	return NULL;
}

void CXML::nodeSetContent(const char * content)
{
	if(m_node)
	{
		m_node->Clear();
		// This could cause leaks?
		TiXmlText * newNode = new TiXmlText(content);
		m_node->LinkEndChild(newNode);
	}
}

void CXML::nodeToRoot()
{
	m_node = m_document.RootElement();
}

bool CXML::findNode(const char * name)
{
	if(m_node && m_node->FirstChild(name) != 0)
	{
		m_node = m_node->FirstChild(name)->ToElement();
		return true;
	}

	return false;
}

bool CXML::nextNode()
{
	if(m_node && m_node->NextSibling() != 0)
	{
		m_node = m_node->NextSibling()->ToElement();
		return true;
	}

	return false;
}

bool CXML::previousNode()
{
	if(m_node && m_node->PreviousSibling() != 0)
	{
		m_node = m_node->PreviousSibling()->ToElement();
		return true;
	}

	return false;
}

bool CXML::childNodeFirst()
{
	if(m_node && m_node->FirstChild() != 0)
	{
		m_node = m_node->FirstChild()->ToElement();
		return true;
	}

	return false;
}

void CXML::nodeParent()
{
	if(m_node && m_node->Parent())
	{
		m_node = m_node->Parent()->ToElement();
	}
}

void CXML::nodeClear()
{
	if(m_node)
	{
		m_node->Clear();
	}
}

void CXML::newNode(const char * name, bool nodePointerToNewNode)
{
	if(nodePointerToNewNode == true)
	{
		// This could cause leaks?
		m_node = new TiXmlElement(name);
		m_node->LinkEndChild(m_node);
	}
	else
	{
		if(m_node)
		{
			// This could cause leaks?
			TiXmlElement * newNode = new TiXmlElement(name);
			m_node->LinkEndChild(newNode);
		}
	}
}

void CXML::newComment(const char * comment)
{
	if(m_node)
	{
		TiXmlComment * newComment = new TiXmlComment(comment);
		m_node->LinkEndChild(newComment);
	}
}

const char * CXML::lastError(int * iErrorRow, int * iErrorCol)
{
	if(m_document.Error())
	{
		if(iErrorRow)
		{
			*iErrorRow = m_document.ErrorCol();
		}

		if(iErrorCol)
		{
			*iErrorCol = m_document.ErrorRow();
		}

		return m_document.ErrorDesc();
	}

	return NULL;
}

bool CXML::isComment()
{
	if(m_node && m_node->Type() == TiXmlNode::COMMENT)
	{
		return true;
	}

	return false;
}