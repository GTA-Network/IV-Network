#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Controls/GroupBox.h"

using namespace Gwen;

class GroupBox : public GUnit
{
	public:

	GWEN_CONTROL_INLINE( GroupBox, GUnit )
	{
		Gwen::Controls::GroupBox* pGroup = new Gwen::Controls::GroupBox( this );
		pGroup->Dock( Pos::Fill );
		pGroup->SetText( "Group Box" );
	}
};



DEFINE_UNIT_TEST( GroupBox, L"GroupBox" );