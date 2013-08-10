/*  RendererPng.h
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

#ifndef glbarcode_RendererPng_h
#define glbarcode_RendererPng_h

#if HAVE_LIBPNG

#include "Renderer.h"


namespace glbarcode
{

	/**
	 * Simple PNG Renderer
	 *
	 * Renders Portable Network Graphics format
	 */
	class RendererPng : public Renderer
	{
	public:
		RendererPng( std::string filename, double ppi );

	private:
		void draw_begin( double w, double h );
		void draw_end( void );

		void draw_line( PrimitiveLine *line );
		void draw_box( PrimitiveBox *box );
		void draw_text( PrimitiveText *text );
		void draw_ring( PrimitiveRing *ring );
		void draw_hexagon( PrimitiveHexagon *hexagon );

	private:
		std::string m_filename;
		double      m_scale_ppp;

		int         m_w_pixels;
		int         m_h_pixels;
		int         m_total_pixels;

		char       *m_buffer;
	};

}

#endif // HAVE_LIBPNG

#endif // glbarcode_RendererPng_h
