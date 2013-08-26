#include <glbarcode/BarcodeFactory.h>
#include <glbarcode/RendererSvg.h>

using namespace glbarcode;

int main( int argc, char **argv )
{
	/* Get singleton instance to barcode factory. */
        BarcodeFactory *factory = BarcodeFactory().instance();

	/* Show text and generate check digit. */
	BarcodeOptions options = BarcodeOptions().checksum(true).show_text(true);

        /* Create barcode object. */
        Barcode *bc = factory->create_barcode( "code39", "EXAMPLE-123", 288, 72, options );

        /* Render barcode. */
        bc->render( RendererSvg().filename( "Example.svg" ) );

	/* Cleanup. */
        delete bc;
}
