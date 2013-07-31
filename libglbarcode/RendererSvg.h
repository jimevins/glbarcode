/*  RendererSvg.h
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
 *
 *  This file is part of glbarcode++.
 *
 *  glbarcode++ is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  glbarcode++ is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with glbarcode++.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef glbarcode_RendererSvg_h
#define glbarcode_RendererSvg_h


#include "Renderer.h"


namespace glbarcode
{

	class RendererSvg : public Renderer
	{
	protected:
		virtual void draw_begin( double w, double h );
		virtual void draw_end( void );

		virtual void draw_box( PrimitiveBox *box );
		virtual void draw_text( PrimitiveText *text );
		virtual void draw_ring( PrimitiveRing *ring );
		virtual void draw_hexagon( PrimitiveHexagon *hexagon );
	};

}

#endif // glbarcode_RendererSvg_h
