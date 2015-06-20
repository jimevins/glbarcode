/* main.cpp */

#include "MyBarcode.h"

#include <glbarcode/Factory.h>
#include <glbarcode/RendererSvg.h>
 
using namespace glbarcode;
 
int main( int argc, char **argv )
{
	/* Register my barcode with factory. */
	Factory::registerType( "mybarcode", MyBarcode::create );

        /* Create barcode object. */
        Barcode *bc = Factory::createBarcode( "mybarcode" );
 
	/* Set barcode options to show text and generate check digit, and then build */
	bc->setChecksum(true).setShowText(true).build( "c0de0016", 288, 72 );
 
        /* Render barcode. */
        bc->render( RendererSvg().setFilename( "MyBarcodeExample.svg" ) );
 
	/* Cleanup. */
        delete bc;
}
