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
	glbarcode::Barcode* bc;

	/*
	 * Initialize barcode factory.
	 */
	glbarcode::Factory::init();

	/*
	 * Code39
	 */
	bc = glbarcode::Factory::createBarcode( "code39" );
	bc->show_text(true).checksum(true).build( "ABC123", 216, 72 );
	bc->render( RendererSvg().filename( "sample-code39.svg" ) );
	delete bc;

	/*
	 * Extended Code39
	 */
	bc = glbarcode::Factory::createBarcode( "code39ext" );
	bc->show_text(true).checksum(true).build( "Abc123", 216, 72 );
	bc->render( RendererSvg().filename( "sample-code39ext.svg" ) );
	delete bc;

	/*
	 * UPC-A
	 */
	bc = glbarcode::Factory::createBarcode( "upc-a" );
	bc->build( "12345678901", 162, 81 );
	bc->render( RendererSvg().filename( "sample-upc-a.svg" ) );
	delete bc;

	/*
	 * EAN-13
	 */
	bc = glbarcode::Factory::createBarcode( "ean-13" );
	bc->build( "123456789012", 162, 81 );
	bc->render( RendererSvg().filename( "sample-ean-13.svg" ) );
	delete bc;

	/*
	 * POSTNET
	 */
	bc = glbarcode::Factory::createBarcode( "postnet" );
	bc->build( "12345678901", 0, 0 );
	bc->render( RendererSvg().filename( "sample-postnet.svg" ) );
	delete bc;

	/*
	 * POSTNET-5
	 */
	bc = glbarcode::Factory::createBarcode( "postnet-5" );
	bc->build( "12345", 0, 0 );
	bc->render( RendererSvg().filename( "sample-postnet-5.svg" ) );
	delete bc;

	/*
	 * POSTNET-9
	 */
	bc = glbarcode::Factory::createBarcode( "postnet-9" );
	bc->build( "123456789", 0, 0 );
	bc->render( RendererSvg().filename( "sample-postnet-9.svg" ) );
	delete bc;

	/*
	 * POSTNET-11
	 */
	bc = glbarcode::Factory::createBarcode( "postnet-11" );
	bc->build( "12345678901", 0, 0 );
	bc->render( RendererSvg().filename( "sample-postnet-11.svg" ) );
	delete bc;

	/*
	 * CEPNET
	 */
	bc = glbarcode::Factory::createBarcode( "cepnet" );
	bc->build( "12345678", 0, 0 );
	bc->render( RendererSvg().filename( "sample-cepnet.svg" ) );
	delete bc;

	/*
	 * ONECODE
	 */
	bc = glbarcode::Factory::createBarcode( "onecode" );
	bc->build( "12345678901234567890", 0, 0 );
	bc->render( RendererSvg().filename( "sample-onecode.svg" ) );
	delete bc;

	/*
	 * DataMatrix
	 */
	bc = glbarcode::Factory::createBarcode( "datamatrix" );
	bc->build( "Data Matrix ECC200", 0, 0 );
	bc->render( RendererSvg().filename( "sample-datamatrix.svg" ) );
	delete bc;

	/*
	 * QRCode
	 */
#if HAVE_QRENCODE
	bc = glbarcode::Factory::createBarcode( "qrcode" );
	bc->build( "http://glabels.org/", 0, 0 );
	bc->render( RendererSvg().filename( "sample-qrcode.svg" ) );
	delete bc;
#endif

}
