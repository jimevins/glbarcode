/*  gbc_barcode.cpp
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

#include "gbc_barcode.h"

#include <glbarcode/Barcode.h>


using namespace glbarcode;



void gbc_barcode_delete( gbcBarcode *bc )
{
	delete static_cast<Barcode*>(bc);
}


void gbc_barcode_set_show_text( gbcBarcode *bc, bool value )
{
	static_cast<Barcode*>(bc)->setShowText( value );
}


bool gbc_barcode_get_show_text( gbcBarcode *bc )
{
	return static_cast<Barcode*>(bc)->showText();
}


void gbc_barcode_set_checksum( gbcBarcode *bc, bool value )
{
	static_cast<Barcode*>(bc)->setChecksum( value );
}


bool gbc_barcode_get_checksum( gbcBarcode *bc )
{
	return static_cast<Barcode*>(bc)->checksum();
}


void gbc_barcode_build( gbcBarcode *bc,
			char       *data,
			double      w,
			double      h)
{
	static_cast<Barcode*>(bc)->build( data, w, h );
}



void gbc_barcode_render( gbcBarcode  *bc,
			 gbcRenderer *renderer )
{
	static_cast<Barcode*>(bc)->render( *static_cast<Renderer*>(renderer) );
}


bool gbc_barcode_is_empty( gbcBarcode *bc )
{
	return static_cast<Barcode*>(bc)->isEmpty();
}


bool gbc_barcode_is_data_valid( gbcBarcode *bc )
{
	return static_cast<Barcode*>(bc)->isDataValid();
}


double gbc_barcode_get_width( gbcBarcode *bc )
{
	return static_cast<Barcode*>(bc)->width();
}


double gbc_barcode_get_height( gbcBarcode *bc )
{
	return static_cast<Barcode*>(bc)->height();
}



