/*  gbc_factory.cpp
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

#include "gbc_factory.h"

#include <glbarcode/Factory.h>

#include <string>
#include <string.h>
#include <stdlib.h>


using namespace glbarcode;



gbcFactory *gbc_factory_instance( void )
{
	return Factory::instance();
}


gbcBarcode *gbc_factory_create_barcode( gbcFactory *factory,
					char       *type_id )
{
	return static_cast<Factory*>(factory)->create_barcode( type_id );
}


bool gbc_factory_is_type_supported( gbcFactory *factory,
				    char       *type_id )
{
	return static_cast<Factory*>(factory)->is_type_supported( type_id );
}


char ** gbc_factory_get_supported_types( gbcFactory  *factory )
{
	std::vector<std::string> supported_types = static_cast<Factory*>(factory)->get_supported_types();
	int n = supported_types.size();

	char **list = new char*[ n + 1 ];

	for ( int i = 0; i < n; i++ )
	{
		list[i] = strdup( supported_types[i].c_str() );
	}
	list[n] = NULL;

	return list;
}


void gbc_factory_free_supported_types( char **list )
{
	for ( int i = 0; list[i] != NULL; i++ )
	{
		free( list[i] ); /* use free() since allocated w/ strdup() */
	}
	delete[] list;
}
