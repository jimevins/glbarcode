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


void glbarcode::Renderer::render( double w, double h, std::list<DrawingPrimitive*> primitives )
{
	drawBegin( w, h );

	std::list<DrawingPrimitive*>::iterator primitive;

	for ( primitive = primitives.begin(); primitive != primitives.end(); primitive++ )
	{
		if ( DrawingPrimitiveLine* line = dynamic_cast<DrawingPrimitiveLine*>(*primitive) )
		{
			drawLine( line );
		}
		else if ( DrawingPrimitiveBox* box = dynamic_cast<DrawingPrimitiveBox*>(*primitive) )
		{
			drawBox( box );
		}
		else if ( DrawingPrimitiveText* text = dynamic_cast<DrawingPrimitiveText*>(*primitive) )
		{
			drawText( text );
		}
		else if ( DrawingPrimitiveRing* ring = dynamic_cast<DrawingPrimitiveRing*>(*primitive) )
		{
			drawRing( ring );
		}
		else if ( DrawingPrimitiveHexagon* hex = dynamic_cast<DrawingPrimitiveHexagon*>(*primitive) )
		{
			drawHexagon( hex );
		}
		else
		{
			// NOT REACHED
		}
	}

	drawEnd();
}
