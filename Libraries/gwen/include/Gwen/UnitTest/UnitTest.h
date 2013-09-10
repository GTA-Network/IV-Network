/*
	GWEN
	Copyright (c) 2011 Facepunch Studios
	See license in Gwen.h
*/


#pragma once
#include "Gwen/Gwen.h"
#include "Gwen/Align.h"
#include "Gwen/Utility.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/ListBox.h"

class UnitTest;

#ifdef _MSC_VER
#	ifdef NDEBUG
#		pragma comment ( lib, "unittest.lib" )
#	else
#		pragma comment ( lib, "unittestd.lib" )
#	endif
#endif


class GUnit : public Gwen::Controls::Base
{
	public:

		GWEN_CONTROL_INLINE( GUnit, Gwen::Controls::Base )
		{
			m_pUnitTest = NULL;
		}

		void SetUnitTest( UnitTest* u ){ m_pUnitTest = u; }

		void UnitPrint( const Gwen::UnicodeString& str );
		void UnitPrint( const Gwen::String& str );

		


		UnitTest* m_pUnitTest;
};

class UnitTest : public Gwen::Controls::WindowControl
{
	public:

		GWEN_CONTROL( UnitTest, Gwen::Controls::WindowControl );

		void PrintText( const Gwen::UnicodeString& str );

		void Render( Gwen::Skin::Base* skin );


	private:

		Gwen::Controls::TabControl*	m_TabControl;
		Gwen::Controls::ListBox*	m_TextOutput;
		unsigned int				m_iFrames;
		float						m_fLastSecond;

};

#define DEFINE_UNIT_TEST( name, displayname ) GUnit* RegisterUnitTest_##name( Gwen::Controls::TabControl* tab ){ GUnit* u = new name( tab ); tab->AddPage( displayname, u ); return u; }
