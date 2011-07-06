#ifndef __SMALLCHAR_H
#define __SMALLCHAR_H

#include <string>

/*
#include "variant.h"
#include "text.h"
#include "double.h"
#include "integer.h"

*/
class SMADDOUBLE;
class SMADINTEGER;
class SMADSMALLCHAR;
class SMADTEXT;
class SMADVARIANT;


/*
PROTOTYPES FOR FRIEND FUNCTIONS
*/
//******************************************

	 SMADSMALLCHAR operator+(const char* s,
		SMADSMALLCHAR ob);
	 SMADSMALLCHAR operator+(const string& s,
		SMADSMALLCHAR ob);
	 istream& operator>>(istream& , SMADSMALLCHAR&);
	 ostream& operator<<(ostream&, const SMADSMALLCHAR&);

	
	 bool operator<(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	 bool operator<(const SMADSMALLCHAR&, const string&);
	 bool operator<(const string&,const SMADSMALLCHAR&);
	 bool operator<(const SMADSMALLCHAR&, const char* );
	 bool operator<(const char*, const SMADSMALLCHAR&);
	
	
	 bool operator>(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	 bool operator>(const SMADSMALLCHAR&, const string&);
	 bool operator>(const string&,const SMADSMALLCHAR&);
	 bool operator>(const SMADSMALLCHAR&, const char* );
	 bool operator>(const char*, const SMADSMALLCHAR&);

	 bool operator<=(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	 bool operator<=(const SMADSMALLCHAR&, const string&);
	 bool operator<=(const string&,const SMADSMALLCHAR&);
	 bool operator<=(const SMADSMALLCHAR&, const char* );
	 bool operator<=(const char*, const SMADSMALLCHAR&);
	
	 bool operator>=(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	 bool operator>=(const SMADSMALLCHAR&, const string&);
	 bool operator>=(const string&,const SMADSMALLCHAR&);
	 bool operator>=(const SMADSMALLCHAR&, const char* );
	 bool operator>=(const char*, const SMADSMALLCHAR&);

	 bool operator==(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	 bool operator==(const SMADSMALLCHAR&, const string&);
	 bool operator==(const string&,const SMADSMALLCHAR&);
	 bool operator==(const SMADSMALLCHAR&, const char* );
	 bool operator==(const char*, const SMADSMALLCHAR&);

	 bool operator!=(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	 bool operator!=(const SMADSMALLCHAR&, const string&);
	 bool operator!=(const string&,const SMADSMALLCHAR&);
	 bool operator!=(const SMADSMALLCHAR&, const char* );
	 bool operator!=(const char*, const SMADSMALLCHAR&);

//*******************************************

class SMADSMALLCHAR {
private:
	string data;


public:
	SMADSMALLCHAR();
	SMADSMALLCHAR(const string&);
		
	SMADSMALLCHAR (const char*);
	SMADSMALLCHAR (const SMADSMALLCHAR&);
	SMADSMALLCHAR& operator=(const SMADSMALLCHAR&);
	SMADSMALLCHAR& operator=(const string&);
    SMADSMALLCHAR& operator=(const char*);
	SMADSMALLCHAR& operator=(const SMADTEXT&);


	//CONVERSION FUNCTIONS
	operator SMADDOUBLE();
	operator SMADINTEGER();
	operator SMADTEXT();
	operator long();
	operator double();
	operator char*();
	operator string();
	operator SMADVARIANT();


	int serialize(smadfiler&);
	int deserialize(smadfiler&);
	SMADSMALLCHAR operator+(SMADSMALLCHAR);
	SMADSMALLCHAR operator+(const string&);
	SMADSMALLCHAR operator+(const char*);
	SMADSMALLCHAR operator+(SMADTEXT);
	
	SMADSMALLCHAR& operator+=(SMADSMALLCHAR);
	SMADSMALLCHAR& operator+=(const string&);
	SMADSMALLCHAR& operator+=(const char* s);
	SMADSMALLCHAR& operator+=(SMADTEXT);

	//return the data as a string

	const string& value() const;
	const char* value(char* s) const;
	string setvalue(const string&);
	char* setvalue(const char*);


	friend SMADSMALLCHAR operator+(const char* s,
		SMADSMALLCHAR ob);
	friend SMADSMALLCHAR operator+(const string& s,
		SMADSMALLCHAR ob);
	friend istream& operator>>(istream& , SMADSMALLCHAR&);
	friend ostream& operator<<(ostream&, const SMADSMALLCHAR&);

	
	friend bool operator<(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	friend bool operator<(const SMADSMALLCHAR&, const string&);
	friend bool operator<(const string&,const SMADSMALLCHAR&);
	friend bool operator<(const SMADSMALLCHAR&, const char* );
	friend bool operator<(const char*, const SMADSMALLCHAR&);
	
	
	friend bool operator>(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	friend bool operator>(const SMADSMALLCHAR&, const string&);
	friend bool operator>(const string&,const SMADSMALLCHAR&);
	friend bool operator>(const SMADSMALLCHAR&, const char* );
	friend bool operator>(const char*, const SMADSMALLCHAR&);

	friend bool operator<=(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	friend bool operator<=(const SMADSMALLCHAR&, const string&);
	friend bool operator<=(const string&,const SMADSMALLCHAR&);
	friend bool operator<=(const SMADSMALLCHAR&, const char* );
	friend bool operator<=(const char*, const SMADSMALLCHAR&);
	
	friend bool operator>=(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	friend bool operator>=(const SMADSMALLCHAR&, const string&);
	friend bool operator>=(const string&,const SMADSMALLCHAR&);
	friend bool operator>=(const SMADSMALLCHAR&, const char* );
	friend bool operator>=(const char*, const SMADSMALLCHAR&);

	friend bool operator==(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	friend bool operator==(const SMADSMALLCHAR&, const string&);
	friend bool operator==(const string&,const SMADSMALLCHAR&);
	friend bool operator==(const SMADSMALLCHAR&, const char* );
	friend bool operator==(const char*, const SMADSMALLCHAR&);

	friend bool operator!=(const SMADSMALLCHAR&,const SMADSMALLCHAR&);
	friend bool operator!=(const SMADSMALLCHAR&, const string&);
	friend bool operator!=(const string&,const SMADSMALLCHAR&);
	friend bool operator!=(const SMADSMALLCHAR&, const char* );
	friend bool operator!=(const char*, const SMADSMALLCHAR&);

	
		};

#endif
