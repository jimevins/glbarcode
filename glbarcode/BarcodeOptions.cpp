/*  BarcodeOptions.cpp
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

#include "BarcodeOptions.h"


namespace glbarcode
{

	struct BarcodeOptions::PrivateData
	{
		bool m_show_text_flag; /**< Display text flag */
		bool m_checksum_flag;  /**< Add checksum flag */
	};


	BarcodeOptions::BarcodeOptions()
	{
		d = new BarcodeOptions::PrivateData;

		d->m_show_text_flag  = false;
		d->m_checksum_flag   = false;
	}


	BarcodeOptions::BarcodeOptions(const BarcodeOptions& from)
	{
		d = new BarcodeOptions::PrivateData;

		*d = *from.d;
	}


	BarcodeOptions::~BarcodeOptions()
	{
		delete d;
	}


	BarcodeOptions& BarcodeOptions::operator=(const BarcodeOptions& from)
	{
		*d = *from.d;

		return *this;
	}


	BarcodeOptions& BarcodeOptions::show_text( bool value )
	{
		d->m_show_text_flag = value;
		return *this;
	}


	bool BarcodeOptions::show_text( void ) const
	{
		return d->m_show_text_flag;
	}


	BarcodeOptions& BarcodeOptions::checksum( bool value )
	{
		d->m_checksum_flag = value;
		return *this;
	}


	bool BarcodeOptions::checksum( void ) const
	{
		return d->m_checksum_flag;
	}

}
