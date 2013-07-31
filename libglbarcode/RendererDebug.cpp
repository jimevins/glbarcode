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

#include "RendererDebug.h"

#include <stdio.h>


void glbarcode::RendererDebug::draw_begin( double w, double h )
{
	printf( "DRAW_BEGIN( w = %f, h = %f )\n", w, h );
}


void glbarcode::RendererDebug::draw_end( void )
{
	printf( "DRAW_END()\n\n" );
}


void glbarcode::RendererDebug::draw_box( PrimitiveBox *box )
{
	printf( "\tDRAW_BOX( x = %f, y = %f, w = %f, h = %f )\n",
		box->x, box->y, box->w, box->h );
}


void glbarcode::RendererDebug::draw_text( PrimitiveText *text )
{
	printf( "\tDRAW_TEXT( x = %f, y = %f, fsize = %f, s = \"%s\" )\n",
		text->x, text->y, text->fsize, text->s.c_str() );
}


void glbarcode::RendererDebug::draw_ring( PrimitiveRing *ring )
{
	printf( "\tDRAW_RING( x = %f, y = %f, r = %f, line_width = %f )\n",
		ring->x, ring->y, ring->r, ring->line_width );
}


void glbarcode::RendererDebug::draw_hexagon( PrimitiveHexagon *hexagon )
{
	printf( "\tDRAW_HEXAGON( x = %f, y = %f, h = %f )\n",
		hexagon->x, hexagon->y, hexagon->h );
}


