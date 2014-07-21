/*  RendererDebug.h
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

#ifndef glbarcode_RendererDebug_h
#define glbarcode_RendererDebug_h


#include "Renderer.h"

#include <cstdio>


namespace glbarcode
{

	/**
	 * @class RendererDebug RendererDebug.h glbarcode/RendererDebug.h
	 *
	 * Simple text renderer for debug and testing.
	 */
	class RendererDebug : public Renderer
	{

	private:

		void drawBegin( double w, double h )
		{
			printf( "DRAW_BEGIN( w = %f, h = %f )\n", w, h );
		}


		void drawEnd( void )
		{
			printf( "DRAW_END()\n\n" );
		}


		void drawLine( const DrawingPrimitiveLine* line )
		{
			printf( "\tDRAW_LINE( x = %f, y = %f, w = %f, h = %f )\n",
				line->x, line->y, line->w, line->h );
		}


		void drawBox( const DrawingPrimitiveBox* box )
		{
			printf( "\tDRAW_BOX( x = %f, y = %f, w = %f, h = %f )\n",
				box->x, box->y, box->w, box->h );
		}


		void drawText( const DrawingPrimitiveText* text )
		{
			printf( "\tDRAW_TEXT( x = %f, y = %f, fsize = %f, s = \"%s\" )\n",
				text->x, text->y, text->fsize, text->s.c_str() );
		}


		void drawRing( const DrawingPrimitiveRing* ring )
		{
			printf( "\tDRAW_RING( x = %f, y = %f, r = %f, lwidth = %f )\n",
				ring->x, ring->y, ring->r, ring->lwidth );
		}


		void drawHexagon( const DrawingPrimitiveHexagon* hexagon )
		{
			printf( "\tDRAW_HEXAGON( x = %f, y = %f, h = %f )\n",
				hexagon->x, hexagon->y, hexagon->h );
		}

	};

}

#endif // glbarcode_RendererDebug_h
