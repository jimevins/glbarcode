/*  glb_barcode_factory.h
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

#ifndef glb_barcode_factory_h
#define glb_barcode_factory_h


#include "glb_barcode.h"


#ifdef __cplusplus
extern "C" {
#endif


	/**
	 * @struct glbBarcodeFactory glb-barcode-factory.h glbarcode/capi/glb-barcode-factory.h
	 *
	 * CAPI Barcode factory.
	 */
	typedef struct glbBarcodeFactory glbBarcodeFactory;
	

	/**
	 * Get singleton instance of glbBarcodeFactory object.
	 */
	glbBarcodeFactory *glb_barcode_factory_instance( void );


	/**
	 * Create barcode based on type ID string.
	 *
	 * @param type_id Barcode type ID string
	 */
	glbBarcode *glb_barcode_factory_create_barcode( glbBarcodeFactory *factory,
							char              *type_id );


	/**
	 * Is barcode type supported?
	 *
	 * @param type_id Barcode type ID string
	 */
	bool glb_barcode_factory_is_type_supported( glbBarcodeFactory *factory,
						    char              *type_id );


	/**
	 * Get list of suppoted types.
	 *
	 * @param[out] list Pointer to Receive newly allocated list of type ID strings. Terminated by NULL.
	 */
	void glb_barcode_factory_get_supported_types( glbBarcodeFactory *factory,
						      char              **list[] );


	/**
	 * Free previously allocated list of suppoted types.
	 *
	 * @param[out] list List of type ID strings. Created by glb_barcode_factory_get_supported_types().
	 */
	void glb_barcode_factory_free_supported_types( glbBarcodeFactory *factory,
						       char              *list[] );



#ifdef __cplusplus
}
#endif


#endif // glb_barcode_factory_h
