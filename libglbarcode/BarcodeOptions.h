/*  BarcodeOptions.h
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

#ifndef glbarcode_BarcodeOptions_h
#define glbarcode_BarcodeOptions_h


namespace glbarcode
{

	class BarcodeOptions
	{
	public:
		BarcodeOptions( void )
			: m_text_flag( false )
			, m_checksum_flag( false )
		{
		}


		BarcodeOptions& text( bool text_flag )
		{
			m_text_flag = text_flag; return *this;
		}


		BarcodeOptions& checksum( bool checksum_flag )
		{
			m_checksum_flag = checksum_flag; return *this;
		}


	public:
		bool m_text_flag;      /**< Display text flag */
		bool m_checksum_flag;  /**< Add checksum flag */
	};

}


#endif // glbarcode_BarcodeOptions_h
