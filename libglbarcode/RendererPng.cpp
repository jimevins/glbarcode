/*  RendererPng.cpp
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

#include "RendererPng.h"


#if HAVE_LIBPNG

#include "Consts.h"

#include <png.h>
#include <iostream>

namespace glbarcode
{
	RendererPng::RendererPng( std::string filename, double ppi )
	{
		m_filename  = filename;
		m_scale_ppp = ppi / consts::PTS_PER_INCH; /* Pixels per point */
	}


	void RendererPng::draw_begin( double w, double h )
	{

		/* Calculate size in pixels */
		m_w_pixels = (int)(m_scale_ppp*w + 0.5);
		m_h_pixels = (int)(m_scale_ppp*h + 0.5);

		int total_pixels = m_w_pixels * m_h_pixels;


		/* Allocate and initialize pixel buffer */
		m_buffer = new char[ total_pixels ];
		for ( int i = 0; i < total_pixels; i++ )
		{
			m_buffer[i] = 0;
		}

	}


	void RendererPng::draw_end( void )
	{

		FILE *fp = fopen( m_filename.c_str(), "w" );
		png_structp png_ptr = png_create_write_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
		png_init_io( png_ptr, fp );


		png_infop info_ptr = png_create_info_struct( png_ptr );
		png_set_IHDR( png_ptr, info_ptr, m_w_pixels, m_h_pixels,
			      8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE );
		png_write_info( png_ptr, info_ptr );


		png_bytep row = new png_byte[ 3 * m_w_pixels * sizeof(png_byte) ];
		for ( int iy = 0; iy < m_h_pixels; iy++ )
		{
			for ( int ix = 0; ix < m_w_pixels; ix++ )
			{
				int i = iy * m_w_pixels + ix;

				if ( m_buffer[i] == 0 )
				{
					row[ ix*3     ] = 0xFF;
					row[ ix*3 + 1 ] = 0xFF;
					row[ ix*3 + 2 ] = 0xFF;
				}
				else
				{
					row[ ix*3     ] = 0x00;
					row[ ix*3 + 1 ] = 0x00;
					row[ ix*3 + 2 ] = 0x00;
				}
			}
			png_write_row( png_ptr, row );
		}


		png_write_end(png_ptr, NULL);


		/* Cleanup */
		fclose( fp );
		png_free_data( png_ptr, info_ptr, PNG_FREE_ALL, -1 );
		png_destroy_write_struct( &png_ptr, (png_infopp)NULL );

		delete [] m_buffer;
		delete [] row;

	}


	void RendererPng::draw_line( PrimitiveLine *line )
	{

		std::cout << "line: " << line->x << " " << line->width;

		/* Calculate bounds of shape. */
		int x1 = (int)(m_scale_ppp*(line->x - line->width/2) + 0.5);
		int y1 = (int)(m_scale_ppp*(line->y                ) + 0.5);

		int x2 = x1 + (int)(m_scale_ppp*line->width  + 0.5);
		int y2 = y1 + (int)(m_scale_ppp*line->length + 0.5);

		std::cout << ",  ints: " << x1 << " " << x2 << " -> " << (x2-x1) << "\n";


		/* Fill shape. */
		for ( int iy = y1; iy < y2; iy++ )
		{
			for ( int ix = x1; ix < x2; ix++ )
			{
				int i = iy * m_w_pixels + ix;
				m_buffer[ i ] = 1;
			}
		}

	}


	void RendererPng::draw_box( PrimitiveBox *box )
	{
	}


	void RendererPng::draw_text( PrimitiveText *text )
	{
	}


	void RendererPng::draw_ring( PrimitiveRing *ring )
	{
	}


	void RendererPng::draw_hexagon( PrimitiveHexagon *hexagon )
	{
	}


}

#endif // HAVE_LIBPNG
