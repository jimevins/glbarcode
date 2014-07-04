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



void gbc_factory_init( void )
{
	return Factory::init();
}


gbcBarcode *gbc_factory_create_barcode( char *type_id )
{
	return Factory::createBarcode( type_id );
}


bool gbc_factory_is_type_supported( char *type_id )
{
	return Factory::isTypeSupported( type_id );
}


char ** gbc_factory_get_supported_types( void )
{
	std::vector<std::string> supported_types = Factory::getSupportedTypes();
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
