#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"
#include "Gwen/Utility.h"
#include "Gwen/Font.h"
#include "Gwen/Texture.h"
#include "Gwen/Renderers/SFML.h"



namespace Gwen 
{
	namespace Renderer 
	{

		SFML::SFML( sf::RenderTarget& target ) : m_Target(target)
		{

		}

		SFML::~SFML()
		{

		}

		void SFML::SetDrawColor( Gwen::Color color )
		{
			m_Color.r = color.r;
			m_Color.g = color.g;
			m_Color.b = color.b;
			m_Color.a = color.a;
		}

		void SFML::DrawFilledRect( Gwen::Rect rect )
		{
			Translate(rect);
			m_Target.Draw( sf::Shape::Rectangle( rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, m_Color ) );
		}

		void SFML::DrawLine( int x, int y, int a, int b )
		{
			Translate( x, y );
			Translate( a, b );
			m_Target.Draw( sf::Shape::Line( x, y, a, b, 1.0f, m_Color ) );
		}

		void SFML::LoadFont( Gwen::Font* font )
		{
			font->realsize = font->size * Scale();

			sf::Font* pFont = new sf::Font();

#if SFML_VERSION_MAJOR == 2
			if ( !pFont->LoadFromFile( Utility::UnicodeToString( font->facename ) ) )
#else
			if ( !pFont->LoadFromFile( Utility::UnicodeToString( font->facename ), font->realsize  ) )
#endif
			{
				// Ideally here we should be setting the font to a system default font here.
				delete pFont;

				pFont = const_cast<sf::Font*>( &sf::Font::GetDefaultFont() );
			}
			
			font->data = pFont;
		}

		void SFML::FreeFont( Gwen::Font* pFont )
		{
			if ( !pFont->data ) return;

			sf::Font* font = ((sf::Font*)pFont->data);

			// If this is the default font then don't delete it!
			if ( font != &sf::Font::GetDefaultFont() )
			{
				delete font;
			}

			pFont->data = NULL;
		}

		void SFML::RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text )
		{
			Translate( pos.x, pos.y );

			const sf::Font* pSFFont = (sf::Font*)(pFont->data);

			// If the font doesn't exist, or the font size should be changed
			if ( !pSFFont || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont( pFont );
				LoadFont( pFont );
			}

			if  ( !pSFFont )
			{
				pSFFont = &(sf::Font::GetDefaultFont());
			}

#if SFML_VERSION_MAJOR == 2
			sf::Text sfStr( text );
#else
			sf::String sfStr( text );
#endif
			sfStr.SetFont( *pSFFont );
			sfStr.Move( pos.x, pos.y );

#if SFML_VERSION_MAJOR == 2
			sfStr.SetCharacterSize( pFont->realsize );
#else
			sfStr.SetSize( pFont->realsize );
#endif
			sfStr.SetColor( m_Color );

			m_Target.Draw( sfStr );
		}

		Gwen::Point SFML::MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text )
		{
			const sf::Font* pSFFont = (sf::Font*)(pFont->data);

			// If the font doesn't exist, or the font size should be changed
			if ( !pSFFont || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont( pFont );
				LoadFont( pFont );
			}

			if  ( !pSFFont )
			{
				pSFFont = &(sf::Font::GetDefaultFont());
			}

#if SFML_VERSION_MAJOR == 2
			sf::Text sfStr( text );
#else
			sf::String sfStr( text );
#endif
			sfStr.SetFont( *pSFFont );

#if SFML_VERSION_MAJOR == 2
			sfStr.SetCharacterSize( pFont->realsize );
#else
			sfStr.SetSize( pFont->realsize );
#endif
			sfStr.SetColor( m_Color );

			sf::FloatRect sz = sfStr.GetRect();

#if SFML_VERSION_MAJOR == 2
			return Gwen::Point( sz.Width, sz.Height );
#else
			return Gwen::Point( sz.GetWidth(), sz.GetHeight() );
#endif
		}

		void SFML::StartClip()
		{
			Gwen::Rect rect = ClipRegion();

			// OpenGL's coords are from the bottom left
			// so we need to translate them here.
			{
				GLint view[4];
				glGetIntegerv( GL_VIEWPORT, &view[0] );
				rect.y = view[3] - (rect.y + rect.h);
			}

			glScissor( rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale() );
			glEnable( GL_SCISSOR_TEST );
		};


		void SFML::EndClip()
		{
			glDisable(GL_SCISSOR_TEST);
		};

		void SFML::LoadTexture( Gwen::Texture* pTexture )
		{
			if ( !pTexture ) return;
			if ( pTexture->data ) FreeTexture( pTexture );

			sf::Image* tex = new sf::Image();
			tex->SetSmooth( true );

			if ( !tex->LoadFromFile( pTexture->name.Get() ) )
			{
				delete( tex );
				pTexture->failed = true;
				return;
			}

			pTexture->height = tex->GetHeight();
			pTexture->width = tex->GetWidth();
			pTexture->data = tex;

		};

		void SFML::FreeTexture( Gwen::Texture* pTexture )
		{
			sf::Image* tex = static_cast<sf::Image*>( pTexture->data );

			if ( tex )
			{
				delete tex;
			}

			pTexture->data = NULL;
		}

		void SFML::DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect rect, float u1, float v1, float u2, float v2 )
		{
			const sf::Image* tex = static_cast<sf::Image*>( pTexture->data );

			if ( !tex ) 
				return DrawMissingImage( rect );

			Translate( rect );
			
			tex->Bind();

			glColor4f(1, 1, 1, 1 );

			glBegin( GL_QUADS );
				glTexCoord2f( u1, v1 );		glVertex2f(rect.x,     rect.y);
				glTexCoord2f( u1, v2 );		glVertex2f(rect.x,     rect.y + rect.h);
				glTexCoord2f( u2, v2 );		glVertex2f(rect.x + rect.w, rect.y + rect.h);
				glTexCoord2f( u2, v1 );		glVertex2f(rect.x + rect.w, rect.y) ;
			glEnd();
		}


	
	}
}