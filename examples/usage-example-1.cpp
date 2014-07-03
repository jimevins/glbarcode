#include <glbarcode/Factory.h>
#include <glbarcode/RendererSvg.h>

using namespace glbarcode;

int main( int argc, char **argv )
{
	/* Get singleton instance to barcode factory. */
        Factory *factory = Factory().instance();

        /* Create barcode object. */
        Barcode *bc = factory->createBarcode( "code39" );

	/* Set barcode options to show text and generate check digit, and then build */
	bc->setChecksum(true).setShowText(true).build( "EXAMPLE-123", 288, 72 );

        /* Render barcode. */
        bc->render( RendererSvg().setFilename( "Example.svg" ) );

	/* Cleanup. */
        delete bc;
}
