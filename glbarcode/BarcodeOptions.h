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
		/**
		 * Default onstructor
		 */
		BarcodeOptions();


		/** Copy constructor.
		 * 
		 * @param from The value to copy to this object.
		 */
		BarcodeOptions( const BarcodeOptions& from );


		/**
		 * Destructor
		 */
		virtual ~BarcodeOptions();


		/** Assignment operator.
		 *
		 * @param from The value to assign to this object.
		 *
		 * @returns A reference to this object.
		 */
		BarcodeOptions& operator=( const BarcodeOptions& from );


		/**
		 * Set "show_text" parameter
		 *
		 * @param value Boolean value
		 * @returns reference to this BarcodeOptions object for parameter chaining
		 */
		BarcodeOptions& show_text( bool value );


		/**
		 * Get "show_text" parameter
		 *
		 * @returns value of boolean "show_text" parameter
		 */
		bool show_text( void ) const;


		/**
		 * Set "checksum" parameter
		 *
		 * @param value Boolean value
		 * @returns reference to this BarcodeOptions object for parameter chaining
		 */
		BarcodeOptions& checksum( bool value );


		/**
		 * Get "checksum" parameter
		 *
		 * @returns value of boolean "checksum" parameter
		 */
		bool checksum( void ) const;


	private:
		/**
		 * Barcode options private data
		 */
		struct PrivateData;
		PrivateData *d;

	};

}


#endif // glbarcode_BarcodeOptions_h
