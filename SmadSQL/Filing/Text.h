#ifndef __TEXT_H
#define __TEXT_H

#include <string>

class SMADDOUBLE;
class SMADINTEGER;
class SMADSMALLCHAR;
class SMADTEXT;
class SMADVARIANT;


/*
PROTOTYPES FOR FRIEND FUNCTIONS

*/

//********************************************
     ostream& operator<<(ostream&,const SMADTEXT&);
	 istream& operator>>(istream&,SMADTEXT&);


	 SMADTEXT operator+(const char* s,
		const SMADTEXT& ob);
	 SMADTEXT operator+(const string& s,
		const SMADTEXT& ob);
	
	 bool operator<(const SMADTEXT&,const SMADTEXT&);
	 bool operator<(const SMADTEXT&, const string&);
	 bool operator<(const string&,const SMADTEXT&);
	 bool operator<(const SMADTEXT&, const char* );
	 bool operator<(const char*, const SMADTEXT&);
	
	 bool operator>(const SMADTEXT&,const SMADTEXT&);
	 bool operator>(const SMADTEXT&, const string&);
	 bool operator>(const string&,const SMADTEXT&);
	 bool operator>(const SMADTEXT&, const char* );
	 bool operator>(const char*, const SMADTEXT&);

	 bool operator<=(const SMADTEXT&,const SMADTEXT&);
	 bool operator<=(const SMADTEXT&, const string&);
	 bool operator<=(const string&,const SMADTEXT&);
	 bool operator<=(const SMADTEXT&, const char* );
	 bool operator<=(const char*, const SMADTEXT&);
	
	 bool operator>=(const SMADTEXT&,const SMADTEXT&);
	 bool operator>=(const SMADTEXT&, const string&);
	 bool operator>=(const string&,const SMADTEXT&);
	 bool operator>=(const SMADTEXT&, const char* );
	 bool operator>=(const char*, const SMADTEXT&);

	 bool operator==(const SMADTEXT&,const SMADTEXT&);
	 bool operator==(const SMADTEXT&, const string&);
	 bool operator==(const string&,const SMADTEXT&);
	 bool operator==(const SMADTEXT&, const char* );
	 bool operator==(const char*, const SMADTEXT&);

	 bool operator!=(const SMADTEXT&,const SMADTEXT&);
	 bool operator!=(const SMADTEXT&, const string&);
	 bool operator!=(const string&,const SMADTEXT&);
	 bool operator!=(const SMADTEXT&, const char* );
	 bool operator!=(const char*, const SMADTEXT&);

//*******************************************
	
class SMADTEXT {
private:
   string data;

public:
	SMADTEXT();
	SMADTEXT(const string& s);
	SMADTEXT(const char* s);
	SMADTEXT& operator=(const SMADTEXT& t);
	SMADTEXT& operator=(const string& s);
    SMADTEXT& operator=(const char* s);
	int serialize(smadfiler& o);
	int deserialize(smadfiler& i);
	//CONVERSION FUNCTIONS

	operator SMADDOUBLE();
	operator SMADINTEGER();
	operator long();
	operator double();
	operator SMADSMALLCHAR();
	operator string();
	operator char*();
	operator SMADVARIANT();

	
	SMADTEXT operator+(const SMADTEXT& t);
	SMADTEXT operator+(const string& s);
	SMADTEXT operator+(const char* s);
	SMADTEXT& operator+=(const SMADTEXT& t);
	SMADTEXT& operator+=(const string& s);
	SMADTEXT& operator+=(const char* s);
	const string& value()const ;
	const char* value(char* s) const;
	const char* setvalue(const char* );
	const string& setvalue(const string&);

	friend ostream& operator<<(ostream&,const SMADTEXT&);
	friend istream& operator>>(istream&,SMADTEXT&);


	friend SMADTEXT operator+(const char* s,
		const SMADTEXT& ob);
	friend SMADTEXT operator+(const string& s,
		const SMADTEXT& ob);
	
	friend bool operator<(const SMADTEXT&,const SMADTEXT&);
	friend bool operator<(const SMADTEXT&, const string&);
	friend bool operator<(const string&,const SMADTEXT&);
	friend bool operator<(const SMADTEXT&, const char* );
	friend bool operator<(const char*, const SMADTEXT&);
	
	friend bool operator>(const SMADTEXT&,const SMADTEXT&);
	friend bool operator>(const SMADTEXT&, const string&);
	friend bool operator>(const string&,const SMADTEXT&);
	friend bool operator>(const SMADTEXT&, const char* );
	friend bool operator>(const char*, const SMADTEXT&);

	friend bool operator<=(const SMADTEXT&,const SMADTEXT&);
	friend bool operator<=(const SMADTEXT&, const string&);
	friend bool operator<=(const string&,const SMADTEXT&);
	friend bool operator<=(const SMADTEXT&, const char* );
	friend bool operator<=(const char*, const SMADTEXT&);
	
	friend bool operator>=(const SMADTEXT&,const SMADTEXT&);
	friend bool operator>=(const SMADTEXT&, const string&);
	friend bool operator>=(const string&,const SMADTEXT&);
	friend bool operator>=(const SMADTEXT&, const char* );
	friend bool operator>=(const char*, const SMADTEXT&);

	friend bool operator==(const SMADTEXT&,const SMADTEXT&);
	friend bool operator==(const SMADTEXT&, const string&);
	friend bool operator==(const string&,const SMADTEXT&);
	friend bool operator==(const SMADTEXT&, const char* );
	friend bool operator==(const char*, const SMADTEXT&);

	friend bool operator!=(const SMADTEXT&,const SMADTEXT&);
	friend bool operator!=(const SMADTEXT&, const string&);
	friend bool operator!=(const string&,const SMADTEXT&);
	friend bool operator!=(const SMADTEXT&, const char* );
	friend bool operator!=(const char*, const SMADTEXT&);
	
		};

#endif
