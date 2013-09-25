/*  glb_barcode.cpp
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

#include "glb_barcode.h"

#include <glbarcode/Barcode.h>


using namespace glbarcode;



void glb_barcode_delete( glbBarcode *bc )
{
	delete static_cast<Barcode*>(bc);
}


void glb_barcode_set_show_text( glbBarcode *bc, bool value )
{
	static_cast<Barcode*>(bc)->show_text( value );
}


bool glb_barcode_get_show_text( glbBarcode *bc )
{
	return static_cast<Barcode*>(bc)->show_text();
}


void glb_barcode_set_checksum( glbBarcode *bc, bool value )
{
	static_cast<Barcode*>(bc)->checksum( value );
}


bool glb_barcode_get_checksum( glbBarcode *bc )
{
	return static_cast<Barcode*>(bc)->checksum();
}


void glb_barcode_build( glbBarcode *bc,
			char       *data,
			double      w,
			double      h)
{
	static_cast<Barcode*>(bc)->build( data, w, h );
}



void glb_barcode_render( glbBarcode  *bc,
			 glbRenderer *renderer )
{
	static_cast<Barcode*>(bc)->render( *static_cast<Renderer*>(renderer) );
}


bool glb_barcode_is_empty( glbBarcode *bc )
{
	return static_cast<Barcode*>(bc)->is_empty();
}


bool glb_barcode_is_data_valid( glbBarcode *bc )
{
	return static_cast<Barcode*>(bc)->is_data_valid();
}


double glb_barcode_get_width( glbBarcode *bc )
{
	return static_cast<Barcode*>(bc)->width();
}


double glb_barcode_get_height( glbBarcode *bc )
{
	return static_cast<Barcode*>(bc)->height();
}



