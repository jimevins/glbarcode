/*  gbc_factory.h
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

/**
 * @file glbarcode/capi/gbc_factory.h
 *
 * CAPI front-end to glbarcode::Factory.
 */

#ifndef gbc_factory_h
#define gbc_factory_h


#include "gbc_barcode.h"


#ifdef __cplusplus
extern "C" {
#endif


	/**
	 * Initialize barcode factory.
	 */
	void gbc_factory_init( void );


	/**
	 * Create barcode based on type ID string.
	 *
	 * @param type_id Barcode type ID string
	 *
	 * @return Pointer to newly allocated barcode object
	 */
	gbcBarcode *gbc_factory_create_barcode(	char *type_id );


	/**
	 * Is barcode type supported?
	 *
	 * @param type_id Barcode type ID string
	 */
	bool gbc_factory_is_type_supported( char *type_id );


	/**
	 * Get list of suppoted types.
	 *
	 * @return Newly allocated list of type ID strings. Terminated by NULL.
	 */
	char ** gbc_factory_get_supported_types( void );


	/**
	 * Free previously allocated list of suppoted types.
	 *
	 * @param list List of type ID strings. Created by gbc_factory_get_supported_types().
	 */
	void gbc_factory_free_supported_types( char **list );



#ifdef __cplusplus
}
#endif


#endif // gbc_factory_h
