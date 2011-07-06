#ifndef __DOUBLE_H
#define __DOUBLE_H

#include <string>

class SMADDOUBLE;
class SMADINTEGER;
class SMADSMALLCHAR;
class SMADTEXT;
class SMADVARIANT;

/*
#include "variant.h"
#include "text.h"
#include "smallchar.h"
#include "integer.h"
*/



/*
PROTOTYPES FOR FRIEND FUNCTIONS
*/
//******************************************
     
      ostream& operator<<(ostream&,const SMADDOUBLE&);
	  istream& operator>>(istream&,SMADDOUBLE&);
     
	  SMADDOUBLE operator+(double, const SMADDOUBLE&);
	  SMADDOUBLE operator-(double, const SMADDOUBLE&);
	  SMADDOUBLE operator/(double, const SMADDOUBLE&);
	  SMADDOUBLE operator*(double, const SMADDOUBLE&);
	 

      bool operator<(const SMADDOUBLE&, const SMADDOUBLE&);
	  bool operator<(const SMADDOUBLE&, const double);
	  bool operator<(const double, const SMADDOUBLE&);

	  bool operator>(const SMADDOUBLE&, const SMADDOUBLE&);
	  bool operator>(const SMADDOUBLE&, const double);
	  bool operator>(const double, const SMADDOUBLE&);

	  bool operator<=(const SMADDOUBLE&, const SMADDOUBLE&);
	  bool operator<=(const SMADDOUBLE&, const double);
	  bool operator<=(const double, const SMADDOUBLE&);

	  bool operator>=(const SMADDOUBLE&, const SMADDOUBLE&);
	  bool operator>=(const SMADDOUBLE&, const double);
	  bool operator>=(const double, const SMADDOUBLE&);

	  bool operator!=(const SMADDOUBLE&, const SMADDOUBLE&);
	  bool operator!=(const SMADDOUBLE&, const double);
	  bool operator!=(const double, const SMADDOUBLE&);

      bool operator==(const SMADDOUBLE&, const SMADDOUBLE&);
	  bool operator==(const SMADDOUBLE&, const double);
	  bool operator==(const double, const SMADDOUBLE&);

//*****************************************

class SMADDOUBLE{
	double data;

public:
	SMADDOUBLE();
	SMADDOUBLE(const SMADDOUBLE& ob);
    SMADDOUBLE(const double d);

	SMADDOUBLE& operator=(const SMADDOUBLE& ob);
	SMADDOUBLE& operator=(const double d);
	//put raw bin data to stream
	int serialize(smadfiler&);
	//get raw bin data from stream

	int deserialize(smadfiler&);

    double value() const ;
	double setvalue(double)  ;

     operator double();
	 operator long();
	 operator SMADINTEGER();
	 operator SMADSMALLCHAR();
	 operator SMADTEXT();
	 operator string();
	 operator SMADVARIANT();
	 
	 SMADDOUBLE operator+(const SMADDOUBLE& ob);
	 SMADDOUBLE& operator+=(const SMADDOUBLE& ob);
	 SMADDOUBLE operator+(double l);
	 SMADDOUBLE& operator+=(double l);
	 SMADDOUBLE operator-(const SMADDOUBLE& ob);
	 SMADDOUBLE& operator-=(const SMADDOUBLE& ob);
	 SMADDOUBLE operator-(double l);
	 SMADDOUBLE& operator-=(double l);
	 SMADDOUBLE& operator++();
	 SMADDOUBLE& operator++(int);
	 SMADDOUBLE& operator--();
	 SMADDOUBLE& operator--(int);
	 SMADDOUBLE operator*(const SMADDOUBLE& ob);
	 SMADDOUBLE& operator*=(const SMADDOUBLE& ob);
	 SMADDOUBLE operator*(double l);
	 SMADDOUBLE& operator*=(double l);
	 SMADDOUBLE operator/(const SMADDOUBLE& ob);
	 SMADDOUBLE& operator/=(const SMADDOUBLE& ob);
	 SMADDOUBLE operator/(double l);
	 SMADDOUBLE& operator/=(double l);
	 friend ostream& operator<<(ostream&,const SMADDOUBLE&);
	 friend istream& operator>>(istream&,SMADDOUBLE&);

 	 friend SMADDOUBLE operator+(double, const SMADDOUBLE&);
	 friend SMADDOUBLE operator-(double, const SMADDOUBLE&);
	 friend SMADDOUBLE operator/(double, const SMADDOUBLE&);
	 friend SMADDOUBLE operator*(double, const SMADDOUBLE&);
	 

     friend bool operator<(const SMADDOUBLE&, const SMADDOUBLE&);
	 friend bool operator<(const SMADDOUBLE&, const double);
	 friend bool operator<(const double, const SMADDOUBLE&);

	 friend bool operator>(const SMADDOUBLE&, const SMADDOUBLE&);
	 friend bool operator>(const SMADDOUBLE&, const double);
	 friend bool operator>(const double, const SMADDOUBLE&);

	 friend bool operator<=(const SMADDOUBLE&, const SMADDOUBLE&);
	 friend bool operator<=(const SMADDOUBLE&, const double);
	 friend bool operator<=(const double, const SMADDOUBLE&);

	 friend bool operator>=(const SMADDOUBLE&, const SMADDOUBLE&);
	 friend bool operator>=(const SMADDOUBLE&, const double);
	 friend bool operator>=(const double, const SMADDOUBLE&);

	 friend bool operator!=(const SMADDOUBLE&, const SMADDOUBLE&);
	 friend bool operator!=(const SMADDOUBLE&, const double);
	 friend bool operator!=(const double, const SMADDOUBLE&);

     friend bool operator==(const SMADDOUBLE&, const SMADDOUBLE&);
	 friend bool operator==(const SMADDOUBLE&, const double);
	 friend bool operator==(const double, const SMADDOUBLE&);

	};
#endif
