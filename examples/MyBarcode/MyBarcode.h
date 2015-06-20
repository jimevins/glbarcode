/*  MyBarcode.h */

#ifndef _MyBarcode_h_
#define _MyBarcode_h_


#include "glbarcode/Barcode1dBase.h"


class MyBarcode : public glbarcode::Barcode1dBase
{
public:
	static glbarcode::Barcode* create( void );


private:
	bool validate( const std::string& rawData );

	std::string encode( const std::string& cookedData );

	std::string prepareText( const std::string& rawData );

	void vectorize( const std::string& codedData,
	                const std::string& displayText,
	                const std::string& cookedData,
	                double&            w,
	                double&            h );
};


#endif /* _MyBarcode_h_ */
