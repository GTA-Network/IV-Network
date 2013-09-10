
#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"


namespace Gwen 
{
	namespace ControlsInternal
	{
		class Modal : public Controls::Base
		{
			GWEN_CONTROL_INLINE( Modal, Controls::Base )
			{
				SetKeyboardInputEnabled( true );
				SetMouseInputEnabled( true );
				SetShouldDrawBackground( true );
			}
			
			virtual void Layout( Skin::Base* /*skin*/ )
			{
				SetBounds( 0, 0, GetCanvas()->Width(), GetCanvas()->Height() );
			}

			virtual void Render( Skin::Base* skin )
			{
				if ( !ShouldDrawBackground() ) return;

				skin->DrawModalControl( this );
			}
		};
	}
}