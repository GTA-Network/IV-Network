//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CXML.h
// Project: Shared
// Author(s): Einstein
//            jenksta
// License: See LICENSE in root directory
//
//==============================================================================
// TODO: Capitalize function names?

#include <tinyxml/tinyxml.h>
#include <tinyxml/ticpp.h>
#include "SharedUtility.h"
#include "CString.h"

// Notes to EinStein:
// Value = NameOfNode
// Text = InNode

class CXML
{
private:
	TiXmlDocument m_document;
	TiXmlElement * m_node;

public:
	CXML();
	~CXML();

	bool         load(CString strFileName);
	bool         save();
	void         setTabSize(int size);
	const char * getAttribute(const char * attributeName);
	void         removeAttribute(const char * attributeName);
	void         setAttribute(const char * attributeName, const char * value);
	const char * nodeName();
	void         nodeSetName(const char * content);
	const char * nodeContent();
	// Warning: This will delete also child nodes, if they exist
	void         nodeSetContent(const char * content);
	void         nodeToRoot();
	bool         findNode(const char * name);
	bool         nextNode();
	bool         previousNode();
	bool         childNodeFirst();
	void         nodeParent();
	void         nodeClear();
	void         newNode(const char * name, bool nodePointerToNewNode = true);
	void         newComment(const char * comment);
	const char * lastError(int * iErrorRow, int * iErrorCol);
	bool         isComment();
};