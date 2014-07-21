/*  Barcode.cpp
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

#include "Barcode.h"

#include <list>

#include "DrawingPrimitives.h"


namespace glbarcode
{

	/*
	 * Barcode private data
	 */
	struct Barcode::PrivateData {

		bool                   mShowTextFlag;  /**< Display text flag */
		bool                   mChecksumFlag;  /**< Add checksum flag */

		double                 mW;             /**< Width of barcode (points) */
		double                 mH;             /**< Height of barcode (points) */

		bool                   mEmptyFlag;     /**< Empty data flag */
		bool                   mDataValidFlag; /**< Valid data flag */

		std::list<DrawingPrimitive *> mPrimitives;      /**< List of drawing primitives */

	};


	Barcode::Barcode()
	{
		d = new Barcode::PrivateData;

		d->mShowTextFlag  = false;
		d->mChecksumFlag  = false;

		d->mW             = 0;
		d->mH             = 0;

		d->mEmptyFlag     = true;
		d->mDataValidFlag = false;
	}


	Barcode::~Barcode()
	{
		clear(); /* Clear drawing primitives. */
		delete d;
	}


	Barcode& Barcode::setShowText( bool value )
	{
		d->mShowTextFlag = value;
		return *this;
	}


	bool Barcode::showText( void ) const
	{
		return d->mShowTextFlag;
	}


	Barcode& Barcode::setChecksum( bool value )
	{
		d->mChecksumFlag = value;
		return *this;
	}


	bool Barcode::checksum( void ) const
	{
		return d->mChecksumFlag;
	}


	void Barcode::render( Renderer& renderer )
	{
		renderer.render( d->mW, d->mH, d->mPrimitives );
	}


	bool Barcode::isEmpty( void )
	{
		return d->mEmptyFlag;
	}


	void Barcode::setEmptyFlag( bool value )
	{
		d->mEmptyFlag = value;
	}


	bool Barcode::isDataValid( void )
	{
		return d->mDataValidFlag;
	}


	void Barcode::setDataValidFlag( bool value )
	{
		d->mDataValidFlag = value;
	}


	double Barcode::width( void )
	{
		return d->mW;
	}


	double Barcode::height( void )
	{
		return d->mH;
	}


	void Barcode::setWidth( double w )
	{
		d->mW = w;
	}


	void Barcode::setHeight( double h )
	{
		d->mH = h;
	}


	void Barcode::clear( void )
	{
		std::list<DrawingPrimitive*>::iterator primitive;

		for ( primitive = d->mPrimitives.begin(); primitive != d->mPrimitives.end(); primitive++ )
		{
			delete *primitive;
		}

		d->mPrimitives.clear();
	}


	void Barcode::addLine( double x, double y, double w, double h )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveLine( x, y, w, h ) );
	}


	void Barcode::addBox( double x, double y, double w, double h )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveBox( x, y, w, h ) );
	}


	void Barcode::addText( double x, double y, double fsize, std::string s )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveText( x, y, fsize, s ) );
	}


	void Barcode::addRing( double x, double y, double r, double lwidth )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveRing( x, y, r, lwidth ) );
	}


	void Barcode::addHexagon( double x, double y, double h )
	{
		d->mPrimitives.push_back( new DrawingPrimitiveHexagon( x, y, h ) );
	}


}
