#include <glbarcode/Factory.h>
#include <glbarcode/RendererSvg.h>

using namespace glbarcode;

int main( int argc, char **argv )
{
	/* Initialize barcode factory. */
        Factory::init();

        /* Create barcode object. */
        Barcode *bc = Factory::createBarcode( "code39" );

	/* Set barcode options to show text and generate check digit, and then build */
	bc->checksum(true).show_text(true).build( "EXAMPLE-123", 288, 72 );

        /* Render barcode. */
        bc->render( RendererSvg().filename( "Example.svg" ) );

	/* Cleanup. */
        delete bc;
}
