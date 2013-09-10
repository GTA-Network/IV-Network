/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/Dragger.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"

namespace Gwen 
{
	namespace Controls
	{
		class GWEN_EXPORT ResizableControl : public Base
		{
			public:

				GWEN_CONTROL( ResizableControl, Base );

				virtual void SetClampMovement( bool shouldClamp ) { m_bClampMovement = shouldClamp; }
				virtual bool GetClampMovement() { return m_bClampMovement; }

				virtual void SetMinimumSize( const Point& minSize ) { m_MinimumSize = minSize; }
				virtual Point GetMinimumSize() { return m_MinimumSize; }

				virtual void DisableResizing();

				virtual bool SetBounds( int x, int y, int w, int h );

				virtual void OnResized(){};

				Event::Caller	onResize;

			protected:

				void OnResizedInternal( Controls::Base* pControl );

				Point m_MinimumSize;
				bool m_bClampMovement;
				bool m_bResizable;

				
		};
	}
}