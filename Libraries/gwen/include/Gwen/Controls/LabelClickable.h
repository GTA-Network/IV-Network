/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#pragma once
#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Button.h"

namespace Gwen 
{
	namespace Controls
	{
		class GWEN_EXPORT LabelClickable : public Button
		{
			public:

				GWEN_CONTROL( LabelClickable, Button );
				
				virtual void Render( Skin::Base* skin );

		};
	}
}
