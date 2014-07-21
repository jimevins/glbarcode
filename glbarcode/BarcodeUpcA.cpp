/*  BarcodeUpcA.cpp
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

#include "BarcodeUpcA.h"

#include <cctype>
#include <string>


namespace glbarcode
{

	/*
	 * Static UPC-A barcode creation method
	 */
	Barcode* BarcodeUpcA::create( void )
	{
		return new BarcodeUpcA();
	}


	/*
	 * UPC-A barcode constructor
	 */
	BarcodeUpcA::BarcodeUpcA()
	{
		mEndBarsModules = 7;
	}


	/*
	 * UPC-A validate number of digits, implements BarcodeUpcBase::validateDigits()
	 */
	bool BarcodeUpcA::validateDigits( int nDigits )
	{
		return (nDigits == 11);
	}


	/*
	 * UPC-A Pre-process data before encoding, implements Barcode1dBase::preprocess()
	 */
	std::string BarcodeUpcA::preprocess( const std::string& rawData )
	{
		std::string cookedData;

		for ( int i = 0; i < rawData.size(); i++ )
		{
			if ( isdigit( rawData[i] ) )
			{
				cookedData += rawData[i];
			}
		}

		mFirstDigitVal = 0;
		return cookedData;
	}


	/*
	 * UPC-A vectorize text, implements BarcodeUpcBase::vectorizeText()
	 */
	void BarcodeUpcA::vectorizeText( const std::string& displayText,
					 double             size1,
					 double             size2,
					 double             x1Left,
					 double             x1Right,
					 double             y1,
					 double             x2Left,
					 double             x2Right,
					 double             y2 )
	{
		addText( x2Left,  y2, size2, displayText.substr( 0, 1 ) );
		addText( x1Left,  y1, size1, displayText.substr( 1, 5 ) );
		addText( x1Right, y1, size1, displayText.substr( 6, 5 ) );
		addText( x2Right, y2, size2, displayText.substr( 11, 1 ) );
	}

}
