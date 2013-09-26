/*  glb_barcode_factory.cpp
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

#include "glb_barcode_factory.h"

#include <glbarcode/BarcodeFactory.h>

#include <string>
#include <string.h>
#include <stdlib.h>


using namespace glbarcode;



glbBarcodeFactory *glb_barcode_factory_instance( void )
{
	return BarcodeFactory::instance();
}


glbBarcode *glb_barcode_factory_create_barcode( glbBarcodeFactory *factory,
						char              *type_id )
{
	return static_cast<BarcodeFactory*>(factory)->create_barcode( type_id );
}


bool glb_barcode_factory_is_type_supported( glbBarcodeFactory *factory,
					    char              *type_id )
{
	return static_cast<BarcodeFactory*>(factory)->is_type_supported( type_id );
}


char ** glb_barcode_factory_get_supported_types( glbBarcodeFactory  *factory )
{
	std::vector<std::string> supported_types = static_cast<BarcodeFactory*>(factory)->get_supported_types();
	int n = supported_types.size();

	char **list = new char*[ n + 1 ];

	for ( int i = 0; i < n; i++ )
	{
		list[i] = strdup( supported_types[i].c_str() );
	}
	list[n] = NULL;

	return list;
}


void glb_barcode_factory_free_supported_types( char **list )
{
	for ( int i = 0; list[i] != NULL; i++ )
	{
		free( list[i] ); /* use free() since allocated w/ strdup() */
	}
	delete[] list;
}
