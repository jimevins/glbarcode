/*  Simple2dMatrix.h
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

#ifndef glbarcode_Simple2dMatrix_h
#define glbarcode_Simple2dMatrix_h


namespace glbarcode
{

	/**
	 * @class Simple2dMatrix Simple2dMatrix.h glbarcode/Simple2dMatrix.h
	 *
	 * Simple 2D Matrix implementation
	 */
	template <class T> class Simple2dMatrix
	{
		
	public:
		/**
		 * Default constructor.
		 */
		Simple2dMatrix() : m_nx(0), m_ny(0), m_d(NULL) { }


		/**
		 * Sized constructor.
		 */
		Simple2dMatrix( int nx, int ny ) : m_nx(nx),
			                           m_ny(ny),
			                           m_d((nx > 0 && ny > 0) ? new T[nx * ny] : NULL) { }


		/**
		 * Copy constructor.
		 */
		Simple2dMatrix( const Simple2dMatrix<T> & src ) : m_nx(src.m_nx),
			                                          m_ny(src.m_ny),
			                                          m_d((src.m_nx > 0 && src.m_ny > 0) ? new T[src.m_nx * src.m_ny] : NULL)
		{
			for ( int iy = 0; iy < m_ny; iy++ )
			{
				for ( int ix = 0; ix < m_nx; ix++ )
				{
					(*this)[iy][ix] = src[iy][ix];
				}
			}
		}


		/**
		 * Destructor.
		 */
		~Simple2dMatrix()
		{
			if ( m_d != NULL )
			{
				delete[] m_d;
			}
		}


		/**
		 * Indirection "[]" operator
		 */
		inline T* operator[]( int i )
		{
			return (m_d + (m_nx * i));
		}


		/**
		 * Indirection "[]" operator
		 */
		inline T const*const operator[]( int i ) const
		{
			return (m_d + (m_nx * i));
		}


		/**
		 * Resize (destroys old content)
		 */
		inline void resize( int nx, int ny )
		{
			if ( m_d != NULL )
			{
				delete[] m_d;
			}
			m_nx = nx;
			m_ny = ny;
			m_d = (nx > 0 && ny > 0) ? new T[nx * ny] : NULL;
		}


		/**
		 * Get accessor for "nx" parameter.
		 *
		 * @returns Value of "nx" parameter
		 */
		inline int nx( void ) const
		{
			return m_nx;
		}


		/**
		 * Get accessor for "ny" parameter.
		 *
		 * @returns Value of "ny" parameter
		 */
		inline int ny( void ) const
		{
			return m_ny;
		}


		/**
		 * Insert matrix into this matrix
		 */
		inline void insert( int x0, int y0, Simple2dMatrix<T> & a )
		{
			for ( int iy = 0; iy < a.ny(); iy++ )
			{
				if ( (y0 + iy) < m_ny )
				{
					for ( int ix = 0; ix < a.nx(); ix++ )
					{
						if ( (x0 + ix) < m_nx )
						{
							(*this)[y0+iy][x0+ix] = a[iy][ix];
						}
					}
				}
			}
		}


		/**
		 * Fill matrix
		 */
		inline void fill( T val )
		{
			for ( int iy = 0; iy < m_ny; iy++ )
			{
				for ( int ix = 0; ix < m_nx; ix++ )
				{
					(*this)[iy][ix] = val;
				}
			}
		}


	private:
		/**
		 * Simple2dMatrix Private data
		 */
		int m_nx;
		int m_ny;
		T*  m_d;

	};

}


#endif // glbarcode_Simple2dMatrix_h
