/*  MyBarcode.cpp */

#include "MyBarcode.h"

#include "glbarcode/Constants.h"

#include <cctype>
#include <algorithm>


using namespace glbarcode::Constants;


/*-----------------------------------*/
/* Private data.                     */
/*-----------------------------------*/
namespace
{
	/* My barcode alphabet. Position indicates value. */
	const std::string alphabet = "0123456789ABCDEF";

	/* My barcode symbols. Position must match position in alphabet. */
	const std::string symbols[] = {
		/*        BsBsBsBsB */
		/* 0 */  "NnNwWnWnN",
		/* 1 */  "WnNwNnNnW",
		/* 2 */  "NnWwNnNnW",
		/* 3 */  "WnWwNnNnN",
		/* 4 */  "NnNwWnNnW",
		/* 5 */  "WnNwWnNnN",
		/* 6 */  "NnWwWnNnN",
		/* 7 */  "NnNwNnWnW",
		/* 8 */  "WnNwNnWnN",
		/* 9 */  "NnWwNnWnN",
		/* A */  "WnNnNwNnW",
		/* B */  "NnWnNwNnW",
		/* C */  "WnWnNwNnN",
		/* D */  "NnNnWwNnW",
		/* E */  "WnNnWwNnN",
		/* F */  "NnWnWwNnN",
	};

	const std::string frameSymbol = "NwNnWnWnN";

	/* Vectorization constants */
	const double MIN_X       = ( 0.01 *  PTS_PER_INCH );
	const double N           = 2.5;
	const double MIN_I       = MIN_X;
	const double MIN_HEIGHT  = ( 0.25 *  PTS_PER_INCH );
	const double MIN_QUIET   = ( 0.10 *  PTS_PER_INCH );

	const double MIN_TEXT_AREA_HEIGHT = 14.0;
	const double MIN_TEXT_SIZE        = 10.0;

}


/*----------------------------------------------------------------------*/
/* Static barcode creation method                                       */
/*----------------------------------------------------------------------*/
glbarcode::Barcode* MyBarcode::create( void )
{
	return new MyBarcode();
}


/*----------------------------------------------------------------------*/
/* My barcode data validation, implements Barcode1dBase::validate()     */
/*----------------------------------------------------------------------*/
bool MyBarcode::validate( const std::string& rawData )
{
	for ( int i = 0; i < rawData.size(); i++ )
	{
		char c = toupper( rawData[i] );

		if ( alphabet.find(c) == std::string::npos )
		{
			return false;
		}
	}

	return true;
}


/*----------------------------------------------------------------------*/
/* My barcode data encoding, implements Barcode1dBase::encode()         */
/*----------------------------------------------------------------------*/
std::string MyBarcode::encode( const std::string& cookedData )
{
	std::string code;

	/* Left frame symbol */
	code += frameSymbol;
	code += "i";

	int sum = 0;
	for ( int i=0; i < cookedData.size(); i++ )
	{
		int cValue = alphabet.find( toupper( cookedData[i] ) );

		code += symbols[cValue];
		code += "i";

		sum += cValue;
	}

	if ( checksum() )
	{
		code += symbols[sum % 16];
		code += "i";
	}

	/* Right frame symbol */
	code += frameSymbol;

	return code;
}


/*----------------------------------------------------------------------*/
/* Prepare text for display, implements Barcode1dBase::prepareText()    */
/*----------------------------------------------------------------------*/
std::string MyBarcode::prepareText( const std::string& rawData )
{
	std::string displayText;

	for ( int i = 0; i < rawData.size(); i++ )
	{
		displayText += toupper( rawData[i] );
	}

	return displayText;
}


/*----------------------------------------------------------------------*/
/* My barcode vectorization, implements Barcode1dBase::vectorize()      */
/*----------------------------------------------------------------------*/
void MyBarcode::vectorize( const std::string& codedData,
			   const std::string& displayText,
			   const std::string& cookedData,
			   double&            w,
			   double&            h )
{

	/* determine width and establish horizontal scale, based on original cooked data */
	double dataSize = cookedData.size();
	double minL;
	if ( !checksum() )
	{
		minL = (dataSize + 2)*(3*N + 6)*MIN_X + (dataSize + 1)*MIN_I;
	}
	else
	{
		minL = (dataSize + 3)*(3*N + 6)*MIN_X + (dataSize + 2)*MIN_I;
	}
        
	double scale;
	if ( w == 0 )
	{
		scale = 1.0;
	}
	else
	{
		scale = w / (minL + 2*MIN_QUIET);

		if ( scale < 1.0 )
		{
			scale = 1.0;
		}
	}
	double width = minL * scale;

	/* determine text parameters */
	double hTextArea = scale * MIN_TEXT_AREA_HEIGHT;
	double textSize   = scale * MIN_TEXT_SIZE;

	/* determine height of barcode */
	double height = showText() ? h - hTextArea : h;
	height = std::max( height, std::max( 0.15*width, MIN_HEIGHT ) );

	/* determine horizontal quiet zone */
	double xQuiet = std::max( (10 * scale * MIN_X), MIN_QUIET );

	/* Now traverse the code string and draw each bar */
	double x1 = xQuiet;
	for ( int i=0; i < codedData.size(); i++ )
	{
		double lwidth;
				
		switch ( codedData[i] )
		{

		case 'i':
			/* Inter-character gap */
			x1 += scale * MIN_I;
			break;

		case 'N':
			/* Narrow bar */
			lwidth = scale*MIN_X;
			addLine( x1, 0.0, lwidth, height );
			x1 += scale * MIN_X;
			break;

		case 'W':
			/* Wide bar */
			lwidth = scale*N*MIN_X;
			addLine( x1, 0.0, lwidth, height );
			x1 += scale * N * MIN_X;
			break;

		case 'n':
			/* Narrow space */
			x1 += scale * MIN_X;
			break;

		case 'w':
			/* Wide space */
			x1 += scale * N * MIN_X;
			break;

		default:
			// NOT REACHED
			break;
		}
	}

	if ( showText() )
	{
		std::string starredText = "*" + displayText + "*";
		addText( xQuiet + width/2, height + (hTextArea+0.7*textSize)/2, textSize, starredText );
	}

	/* Overwrite requested size with actual size. */
	w = width + 2*xQuiet;
	h = showText() ? height + hTextArea : height;

}
