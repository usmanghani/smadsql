#ifndef __INTEGER_H
#define __INTEGER_H

#include <string>

class SMADINTEGER;
class SMADDOUBLE;
class SMADSMALLCHAR;
class SMADTEXT;
class SMADVARIANT;
class SMADFiler;
typedef SMADFiler smadfiler;


/*
PROTOTYPES FOR FRIEND FUNCTIONS
*/
//****************************************

	  istream& operator>>(istream& , SMADINTEGER&);
	  ostream& operator<<(ostream&, const SMADINTEGER&);

	  SMADINTEGER operator+(long, const SMADINTEGER&);
	  SMADINTEGER operator-(long, const SMADINTEGER&);
	  SMADINTEGER operator/(long, const SMADINTEGER&);
	  SMADINTEGER operator*(long, const SMADINTEGER&);
	  SMADINTEGER operator%(long, const SMADINTEGER&);

      bool operator<(const SMADINTEGER&, const SMADINTEGER&);
	  bool operator<(const SMADINTEGER&, const long);
	  bool operator<(const long, const SMADINTEGER&);

	  bool operator>(const SMADINTEGER&, const SMADINTEGER&);
	  bool operator>(const SMADINTEGER&, const long);
	  bool operator>(const long, const SMADINTEGER&);

	  bool operator<=(const SMADINTEGER&, const SMADINTEGER&);
	  bool operator<=(const SMADINTEGER&, const long);
	  bool operator<=(const long, const SMADINTEGER&);

	  bool operator>=(const SMADINTEGER&, const SMADINTEGER&);
	  bool operator>=(const SMADINTEGER&, const long);
	  bool operator>=(const long, const SMADINTEGER&);

	  bool operator!=(const SMADINTEGER&, const SMADINTEGER&);
	  bool operator!=(const SMADINTEGER&, const long);
	  bool operator!=(const long, const SMADINTEGER&);

      bool operator==(const SMADINTEGER&, const SMADINTEGER&);
	  bool operator==(const SMADINTEGER&, const long);
	  bool operator==(const long, const SMADINTEGER&);

//********************************************

//SMADINTEGER DT

class SMADINTEGER{
	long data;

public:
    SMADINTEGER ();
    SMADINTEGER (long val);
	SMADINTEGER (const SMADINTEGER& ob);
	SMADINTEGER& operator=(const SMADINTEGER& ob);
	//assign a long to SMADINTEGER

	SMADINTEGER& operator=(long ob);
    // put raw bin data to stream
	
	int serialize(smadfiler& o);
	//get raw bin data from stream

	int deserialize(smadfiler& i);
	
	
    long value();
	long setvalue(long);

	 operator long();
	 operator double();
	 operator SMADDOUBLE();
	 operator SMADTEXT();
	 operator SMADSMALLCHAR();
	 operator string();
	 operator SMADVARIANT();


     SMADINTEGER operator+(SMADINTEGER ob);
	 SMADINTEGER& operator+=(SMADINTEGER ob); 
     SMADINTEGER operator+(long l);
	 SMADINTEGER& operator+=(long l);
	 SMADINTEGER operator-(SMADINTEGER ob);	 
	 SMADINTEGER& operator-=(SMADINTEGER ob);

	 SMADINTEGER operator-(long l);
	 SMADINTEGER& operator-=(long l);
	 SMADINTEGER& operator++();
	 SMADINTEGER& operator++(int);
	 SMADINTEGER& operator--();
	 SMADINTEGER& operator--(int);
	 SMADINTEGER operator*(SMADINTEGER ob);
	 SMADINTEGER& operator*=(SMADINTEGER ob);
	 SMADINTEGER operator*(long l);
	 SMADINTEGER& operator*=(long l);

	 SMADINTEGER operator/(SMADINTEGER ob);
	 SMADINTEGER& operator/=(SMADINTEGER ob);
	 SMADINTEGER operator/(long l);
	 SMADINTEGER& operator/=(long l);
     SMADINTEGER operator%(SMADINTEGER ob);
	 SMADINTEGER& operator%=(SMADINTEGER ob);
	 SMADINTEGER operator%(long l);
	 SMADINTEGER& operator%=(long l);
	 friend istream& operator>>(istream& , SMADINTEGER&);
	 friend ostream& operator<<(ostream&, const SMADINTEGER&);

	 friend SMADINTEGER operator+(long, const SMADINTEGER&);
	 friend SMADINTEGER operator-(long, const SMADINTEGER&);
	 friend SMADINTEGER operator/(long, const SMADINTEGER&);
	 friend SMADINTEGER operator*(long, const SMADINTEGER&);
	 friend SMADINTEGER operator%(long, const SMADINTEGER&);

     friend bool operator<(const SMADINTEGER&, const SMADINTEGER&);
	 friend bool operator<(const SMADINTEGER&, const long);
	 friend bool operator<(const long, const SMADINTEGER&);

	 friend bool operator>(const SMADINTEGER&, const SMADINTEGER&);
	 friend bool operator>(const SMADINTEGER&, const long);
	 friend bool operator>(const long, const SMADINTEGER&);

	 friend bool operator<=(const SMADINTEGER&, const SMADINTEGER&);
	 friend bool operator<=(const SMADINTEGER&, const long);
	 friend bool operator<=(const long, const SMADINTEGER&);

	 friend bool operator>=(const SMADINTEGER&, const SMADINTEGER&);
	 friend bool operator>=(const SMADINTEGER&, const long);
	 friend bool operator>=(const long, const SMADINTEGER&);

	 friend bool operator!=(const SMADINTEGER&, const SMADINTEGER&);
	 friend bool operator!=(const SMADINTEGER&, const long);
	 friend bool operator!=(const long, const SMADINTEGER&);

         friend bool operator==(const SMADINTEGER&, const SMADINTEGER&);
	 friend bool operator==(const SMADINTEGER&, const long);
	 friend bool operator==(const long, const SMADINTEGER&);

	};
#endif
