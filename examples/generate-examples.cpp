/*  generate-examples.cpp
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

#include "glbarcode/BarcodeFactory.h"
#include "glbarcode/RendererSvg.h"


using namespace glbarcode;

int main( int argc, char **argv )
{
	glbarcode::BarcodeFactory* factory = glbarcode::BarcodeFactory::instance();
	glbarcode::BarcodeOptions  options = BarcodeOptions().show_text(true).checksum(true);
	glbarcode::Barcode*        bc;

	/*
	 * Code39
	 */
	bc = factory->create_barcode( "code39", "ABC123", 0, 0, options );
	bc->render( RendererSvg().filename( "example-code39.svg" ) );
	delete bc;

	/*
	 * Extended Code39
	 */
	bc = factory->create_barcode( "code39ext", "Abc123", 0, 0, options );
	bc->render( RendererSvg().filename( "example-code39ext.svg" ) );
	delete bc;

	/*
	 * UPC-A
	 */
	bc = factory->create_barcode( "upc-a", "12345678901", 0, 0, options );
	bc->render( RendererSvg().filename( "example-upc-a.svg" ) );
	delete bc;

	/*
	 * EAN-13
	 */
	bc = factory->create_barcode( "ean-13", "123456789012", 0, 0, options );
	bc->render( RendererSvg().filename( "example-ean-13.svg" ) );
	delete bc;

	/*
	 * POSTNET
	 */
	bc = factory->create_barcode( "postnet", "12345678901", 0, 0, options );
	bc->render( RendererSvg().filename( "example-postnet.svg" ) );
	delete bc;

	/*
	 * POSTNET-5
	 */
	bc = factory->create_barcode( "postnet-5", "12345", 0, 0, options );
	bc->render( RendererSvg().filename( "example-postnet-5.svg" ) );
	delete bc;

	/*
	 * POSTNET-9
	 */
	bc = factory->create_barcode( "postnet-9", "123456789", 0, 0, options );
	bc->render( RendererSvg().filename( "example-postnet-9.svg" ) );
	delete bc;

	/*
	 * POSTNET-11
	 */
	bc = factory->create_barcode( "postnet-11", "12345678901", 0, 0, options );
	bc->render( RendererSvg().filename( "example-postnet-11.svg" ) );
	delete bc;

	/*
	 * CEPNET
	 */
	bc = factory->create_barcode( "cepnet", "12345678", 0, 0, options );
	bc->render( RendererSvg().filename( "example-cepnet.svg" ) );
	delete bc;

	/*
	 * ONECODE
	 */
	bc = factory->create_barcode( "onecode", "12345678901234567890", 0, 0, options );
	bc->render( RendererSvg().filename( "example-onecode.svg" ) );
	delete bc;
}
