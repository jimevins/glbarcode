/*  Renderer.h
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

#ifndef glbarcode_Renderer_h
#define glbarcode_Renderer_h


#include <list>

#include "Primitives.h"


namespace glbarcode
{

	class Renderer
	{
	public:
		void render( double w, double h, std::list<Primitive*> primitives );

	protected:
		virtual void draw_begin( double w, double h ) = 0;
		virtual void draw_end( void ) = 0;

		virtual void draw_box( PrimitiveBox *box ) = 0;
		virtual void draw_text( PrimitiveText *text ) = 0;
		virtual void draw_ring( PrimitiveRing *ring ) = 0;
		virtual void draw_hexagon( PrimitiveHexagon *hexagon ) = 0;

	};

}

#endif // glbarcode_Renderer_h
