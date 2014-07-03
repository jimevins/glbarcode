/*  generate-samples.cpp
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

#include "glbarcode/Factory.h"
#include "glbarcode/RendererSvg.h"


using namespace glbarcode;

int main( int argc, char **argv )
{
	glbarcode::Factory* factory = glbarcode::Factory::instance();
	glbarcode::Barcode* bc;

	/*
	 * Code39
	 */
	bc = factory->createBarcode( "code39" );
	bc->setShowText(true).setChecksum(true).build( "ABC123", 216, 72 );
	bc->render( RendererSvg().setFilename( "sample-code39.svg" ) );
	delete bc;

	/*
	 * Extended Code39
	 */
	bc = factory->createBarcode( "code39ext" );
	bc->setShowText(true).setChecksum(true).build( "Abc123", 216, 72 );
	bc->render( RendererSvg().setFilename( "sample-code39ext.svg" ) );
	delete bc;

	/*
	 * UPC-A
	 */
	bc = factory->createBarcode( "upc-a" );
	bc->build( "12345678901", 162, 81 );
	bc->render( RendererSvg().setFilename( "sample-upc-a.svg" ) );
	delete bc;

	/*
	 * EAN-13
	 */
	bc = factory->createBarcode( "ean-13" );
	bc->build( "123456789012", 162, 81 );
	bc->render( RendererSvg().setFilename( "sample-ean-13.svg" ) );
	delete bc;

	/*
	 * POSTNET
	 */
	bc = factory->createBarcode( "postnet" );
	bc->build( "12345678901", 0, 0 );
	bc->render( RendererSvg().setFilename( "sample-postnet.svg" ) );
	delete bc;

	/*
	 * POSTNET-5
	 */
	bc = factory->createBarcode( "postnet-5" );
	bc->build( "12345", 0, 0 );
	bc->render( RendererSvg().setFilename( "sample-postnet-5.svg" ) );
	delete bc;

	/*
	 * POSTNET-9
	 */
	bc = factory->createBarcode( "postnet-9" );
	bc->build( "123456789", 0, 0 );
	bc->render( RendererSvg().setFilename( "sample-postnet-9.svg" ) );
	delete bc;

	/*
	 * POSTNET-11
	 */
	bc = factory->createBarcode( "postnet-11" );
	bc->build( "12345678901", 0, 0 );
	bc->render( RendererSvg().setFilename( "sample-postnet-11.svg" ) );
	delete bc;

	/*
	 * CEPNET
	 */
	bc = factory->createBarcode( "cepnet" );
	bc->build( "12345678", 0, 0 );
	bc->render( RendererSvg().setFilename( "sample-cepnet.svg" ) );
	delete bc;

	/*
	 * ONECODE
	 */
	bc = factory->createBarcode( "onecode" );
	bc->build( "12345678901234567890", 0, 0 );
	bc->render( RendererSvg().setFilename( "sample-onecode.svg" ) );
	delete bc;

	/*
	 * DataMatrix
	 */
	bc = factory->createBarcode( "datamatrix" );
	bc->build( "Data Matrix ECC200", 0, 0 );
	bc->render( RendererSvg().setFilename( "sample-datamatrix.svg" ) );
	delete bc;

	/*
	 * QRCode
	 */
#if HAVE_QRENCODE
	bc = factory->createBarcode( "qrcode" );
	bc->build( "http://glabels.org/", 0, 0 );
	bc->render( RendererSvg().setFilename( "sample-qrcode.svg" ) );
	delete bc;
#endif

}
