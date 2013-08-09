/*  Renderer.cpp
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

#include "Renderer.h"


void glbarcode::Renderer::render( double w, double h, std::list<Primitive*> primitives )
{
	draw_begin( w, h );

	std::list<Primitive*>::iterator primitive;

	for ( primitive = primitives.begin(); primitive != primitives.end(); primitive++ )
	{
		if ( PrimitiveLine *line = dynamic_cast<PrimitiveLine*>(*primitive) )
		{
			draw_line( line );
		}
		else if ( PrimitiveBox *box = dynamic_cast<PrimitiveBox*>(*primitive) )
		{
			draw_box( box );
		}
		else if ( PrimitiveText *text = dynamic_cast<PrimitiveText*>(*primitive) )
		{
			draw_text( text );
		}
		else if ( PrimitiveRing *ring = dynamic_cast<PrimitiveRing*>(*primitive) )
		{
			draw_ring( ring );
		}
		else if ( PrimitiveHexagon *hex = dynamic_cast<PrimitiveHexagon*>(*primitive) )
		{
			draw_hexagon( hex );
		}
		else
		{
			// NOT REACHED
		}
	}

	draw_end();
}
