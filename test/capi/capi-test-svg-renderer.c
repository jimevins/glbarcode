/*  capi-test-svg-renderer.c
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

#include "glbarcode/capi/glb_barcode_factory.h"
#include "glbarcode/capi/glb_renderer_svg.h"

#include <stdio.h>
#include <stdlib.h>


int main( int argc, char **argv )
{
	glbBarcodeFactory *factory;
	glbRenderer       *renderer;
	glbBarcode        *bc;

	if ( argc != 2 )
	{
		fprintf( stderr, "Usage: %s data\n", argv[0] );
		exit( -1 );
	}

	factory = glb_barcode_factory_instance();

	renderer = glb_renderer_svg_new();

	bc = glb_barcode_factory_create_barcode( factory, "code39" );
	glb_barcode_set_checksum( bc, true );
	glb_barcode_set_show_text( bc, true );
	glb_barcode_build( bc, argv[1], 0, 0 );
	glb_barcode_render( bc, renderer );
	glb_barcode_delete( bc );

	glb_renderer_delete( renderer );
}
