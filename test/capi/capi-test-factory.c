/*  capi-test-factory.c
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

#include "glbarcode/capi/gbc_factory.h"

#include <stdio.h>
#include <stdlib.h>


int main( int argc, char **argv )
{
	gbcFactory *factory;
	char **list;
	int i;

	factory = gbc_factory_instance();

	list = gbc_factory_get_supported_types( factory );

	for ( i = 0; list[i] != NULL; i++ )
	{
		printf( "supported_type[%d] = \"%s\"\n", i, list[i] );
	}

	gbc_factory_free_supported_types( list );
}
