/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"
#include "Gwen/Utility.h"


namespace Gwen 
{
	namespace Controls
	{
		namespace Property
		{
			class GWEN_EXPORT Base : public Gwen::Controls::Base
			{
				public:

					GWEN_CONTROL_INLINE( Base, Gwen::Controls::Base ){}

					virtual String GetPropertyValueAnsi()
					{
						return Gwen::Utility::UnicodeToString( GetPropertyValue() );
					}

					virtual void SetPropertyValue( const String& v, bool bFireChangeEvents = false )
					{
						SetPropertyValue( Gwen::Utility::StringToUnicode( v ), bFireChangeEvents );
					}

					virtual UnicodeString GetPropertyValue() = 0;

					virtual void SetPropertyValue( const UnicodeString& v, bool bFireChangeEvents = false ) = 0;

					virtual bool IsEditing() = 0;

					virtual void DoChanged()
					{
						onChange.Call( this );
					}

					virtual void OnPropertyValueChanged( Gwen::Controls::Base* /*control*/ )
					{
						DoChanged();
					}

					Event::Caller	onChange;
			};
		}
	}
}