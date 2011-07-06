#ifndef __VARIANT_H
#define __VARIANT_H

#include <string>

class SMADDOUBLE;
class SMADINTEGER;
class SMADVARIANT;
class SMADTEXT;
class SMADSMALLCHAR;

#include "text.h"
#include "smallchar.h"
#include "double.h"
#include "integer.h"
#include "enumdef.h"

/*
IMPORTANT: READ IT FIRST
  It is to be noted here that type variant
is not a container of data in the real sense
ie itonly contains pointers to actual data
it must be used cautiously
copying one variant into another using the operator=
merely copies the references to the original data
it does not replicate the original data
If data is allocated during copying using
new and then deleted in the destructor 
then still theres a problem
if the had not been allocated inthe first place
wid new the consequences of deletion would be
disastrous
and theres no method of determining whether 
the data was allocated using new or not
by merely inspecting the pointer


*/




class SMADVARIANT;


ostream& operator<<(ostream&, const SMADVARIANT&);
istream& operator>>(istream&, SMADVARIANT&);

bool operator<( const SMADVARIANT& v1, const  SMADVARIANT& v2);
bool operator>( const SMADVARIANT& v1, const  SMADVARIANT& v2);

class SMADVARIANT{
private:

	enum fld_typ type;

	SMADSMALLCHAR* sc;
	SMADDOUBLE* dbl;
	SMADINTEGER* intgr;
	SMADTEXT* txt;

	SMADDOUBLE toDOUBLE();

	SMADINTEGER toINTEGER();

	SMADTEXT toTEXT();

	SMADSMALLCHAR toSMALLCHAR();
	
public:
    enum fld_typ get_type() const;

	void set_type(enum fld_typ t);
	char* getString()
	{
		return static_cast <char*> ( toTEXT() );
	}


    SMADVARIANT();/*:type(typVARIANT){
	sc=intgr=txt=dbl=NULL;
	}
   */ 
	~SMADVARIANT();

	explicit SMADVARIANT(SMADSMALLCHAR* psc);

	explicit SMADVARIANT(SMADTEXT* ptxt);

	explicit SMADVARIANT(SMADINTEGER* pint);

	explicit SMADVARIANT(SMADDOUBLE* pdbl);
    SMADVARIANT& operator=(SMADSMALLCHAR*);
    SMADVARIANT& operator=(SMADTEXT*);
	SMADVARIANT& operator=(SMADINTEGER*);
	SMADVARIANT& operator=(SMADDOUBLE*);
	SMADVARIANT& operator=(const  SMADVARIANT&);
	SMADVARIANT(const SMADVARIANT& v); 
    int serialize(smadfiler&);
	int deserialize(smadfiler&);
    friend ostream& operator<<(ostream&,const SMADVARIANT&);
	friend istream& operator>>(istream&, SMADVARIANT&);
	friend bool operator<( const SMADVARIANT&, const  SMADVARIANT&);
	friend bool operator>( const SMADVARIANT&, const SMADVARIANT&);
	void put_data(SMADSMALLCHAR* psc);
	void put_data(SMADTEXT* ptxt);
	void put_data(SMADDOUBLE* pdbl);
	void put_data(SMADINTEGER* pint);

    
	operator SMADDOUBLE(){
		return toDOUBLE();
	}
	operator SMADINTEGER(){
		return toINTEGER();
	}
	operator SMADSMALLCHAR(){
		return toSMALLCHAR();
	}
	operator SMADTEXT(){
		return toTEXT();
	}
	operator string(){
		return static_cast<string>(toTEXT());
	}
	operator char*(){
		return static_cast<char*>(toTEXT());
	}
	operator long(){
		return static_cast<long>(toTEXT());
	}
	operator double(){
		return static_cast<double>(toTEXT());
	}
	SMADVARIANT& operator+=(  SMADTEXT& t);
	SMADVARIANT& operator+=(  SMADDOUBLE& d);
	SMADVARIANT &operator+=(  SMADINTEGER& i);
	SMADVARIANT &operator+=(  SMADSMALLCHAR& sm);
		


};
/*
SMADVARIANT SMADVARIANT::operator+=( SMADTEXT& t){
		if(type==typTEXT) *txt+=t;
		else {
			switch(type){
			case typDOUBLE:
				*dbl+=(SMADDOUBLE)t;
				break;
			case typINTEGER:
				*intgr+=(SMADINTEGER)t;
				break;
			case typSMALLCHAR:
				*sc+=(SMADSMALLCHAR)t;
				break;
			}
		}

		return *this;
	}
SMADVARIANT SMADVARIANT::operator+=( SMADDOUBLE& d){
		if(type==typDOUBLE) (*dbl)+=d;
		else {
			switch(type){
			case typTEXT:
				*txt+=(SMADTEXT)d;
				break;
			case typINTEGER:
				*intgr+=(SMADINTEGER)d;
				break;
			case typSMALLCHAR:
				*sc+=(SMADSMALLCHAR)d;
				break;
			}
		}

		return *this;
	}
SMADVARIANT SMADVARIANT::operator+=( SMADINTEGER& i){
		if(type==typINTEGER)(*intgr)+=i;
		else {
			switch(type){
			case typTEXT:
				*txt+=(SMADTEXT)i;
				break;
			case typDOUBLE:
				*dbl+=(SMADDOUBLE)i;
				break;
			case typSMALLCHAR:
				*sc+=(SMADSMALLCHAR)i;
				break;
			}
		}

		return *this;
	}
SMADVARIANT SMADVARIANT::operator+=( SMADSMALLCHAR& sm){
		if(type==typSMALLCHAR)(*sc)+=sm;
		else {
			switch(type){
			case typTEXT:
				*txt+=(SMADTEXT)sm;
				break;
			case typDOUBLE:
				*dbl+=(SMADDOUBLE)sm;
				break;
			case typINTEGER:
				*intgr+=(SMADINTEGER)sm;
				break;
			}
		}


		return *this;
	}
	
		


ostream& SMADVARIANT::serialize(ostream& o){
		switch (type){
		case typSMALLCHAR:
			sc->serialize(o);
			break;
		case typTEXT:
			txt->serialize(o);
			break;
		case typINTEGER:
			intgr->serialize(o);
			break;
		case typDOUBLE:
			dbl->serialize(o);
			break;
		}
}
istream& SMADVARIANT::deserialize(istream& i){
		switch(type){
		case typSMALLCHAR: 
			sc->deserialize(i);
			break;
		case typTEXT:
			txt->deserialize(i);
			break;
		case typINTEGER:
			intgr->deserialize(i);
			break;
		case typDOUBLE:
			dbl->deserialize(i);
			break;
		}
}
SMADVARIANT::SMADVARIANT(SMADSMALLCHAR* psc){
		put_data(psc);
		dbl=intgr=txt=NULL;
	}

SMADVARIANT::SMADVARIANT(SMADTEXT* ptxt){
		put_data(ptxt);
		dbl=intgr=sc=NULL;
	}

SMADVARIANT::SMADVARIANT(SMADINTEGER* pint){
		put_data(pint);
		dbl=sc=txt=NULL;
	}
SMADVARIANT::SMADVARIANT(SMADDOUBLE* pdbl){
		put_data(pdbl);
		sc=intgr=txt=NULL;
	}

void SMADVARIANT::set_type(enum fld_typ t){
		type=t;
}
enum fld_typ SMADVARIANT::get_type(){
		return type;
}

SMADVARIANT::SMADVARIANT():type(typVARIANT){
	sc=intgr=txt=dbl=NULL;
}
SMADVARIANT SMADVARIANT::operator=(const SMADVARIANT& v){
	if (type==typVARIANT)
		type=v.type;
		switch (type){
		case typINTEGER:
			intgr=v.intgr;
			break;
		case typDOUBLE:
			dbl=v.dbl;
			break;
		case typTEXT:
			txt=v.txt;
			break;
		case typSMALLCHAR:
			sc=v.sc;
			break;
		}
		return *this;

}

*/	

/*
IMPORTANT: 
CANT DO THESE OPERATIONS 
VARIABLES R REPLICATED ON STACK
TAKING THEIR ADDRESS LL GIVE THE ADDRESS OF
THEE VARS ON THE STACK
CANT USE REFERENCES CZ THEIR ADDRESS
CANT BE TAKEN
POINTERS LL MAKE THE EXPRESSIONS SEEM
UNNATURAL
SMADVARIANT V= &D;
USE PUT_DATA METHOD

SMADVARIANT operator=(const SMADDOUBLE d){
	type=typDOUBLE;
	dbl=&d;
	return *this;

}

SMADVARIANT operator=(const SMADINTEGER i){
	type=typINTEGER;
	intgr=&i;
	return *this;
}

SMADVARIANT operator=(const SMADSMALLCHAR sm){
	type=typSMALLCHAR;
	intgr=&sm;
	return *this;
}

SMADVARIANT operator=(const SMADTEXT t){
	type=typTEXT;
	intgr=&t;
	return *this;
}

*/

/*
	void SMADVARIANT::put_data(SMADSMALLCHAR* psc){
		sc=psc;
		type=typSMALLCHAR;

	}
	void SMADVARIANT::put_data(SMADTEXT* ptxt){
		txt=ptxt;
		type=typTEXT;

	}
	void SMADVARIANT::put_data(SMADDOUBLE* pdbl){
		dbl=pdbl;
		type=typDOUBLE;

	}
	void SMADVARIANT::put_data(SMADINTEGER* pint){
		intgr=pint;
		type=typINTEGER;

	}


	SMADDOUBLE SMADVARIANT::toDOUBLE(){
		switch (type){
		case typINTEGER:
			return *intgr;
			break;
		case typDOUBLE:
			return *dbl;
			break;
		case typTEXT:
			return *txt;
			break;
		case typSMALLCHAR:
			return *sc;
			break;
		}
	}

	SMADINTEGER SMADVARIANT::toINTEGER(){
		switch (type){
		case typINTEGER:
			return *intgr;
		case typDOUBLE:
			return *dbl;
		case typTEXT:
			return *txt;
		case typSMALLCHAR:
			return *sc;
		}
	}

	SMADTEXT SMADVARIANT::toTEXT(){
		switch (type){
		case typTEXT:
			return *txt;
		case typSMALLCHAR:
			return *sc;
		case typINTEGER:
			return *intgr;
		case typDOUBLE:
			return *dbl;
		}
	}
	SMADSMALLCHAR SMADVARIANT::toSMALLCHAR(){
		switch (type){
		case typTEXT:
			return *txt;
		case typSMALLCHAR:
			return *sc;
		case typINTEGER:
			return *intgr;
		case typDOUBLE:
			return *dbl;
		}
	}

ostream& operator<<(ostream& o,const SMADVARIANT& v){
	switch(v.type){
	case typSMALLCHAR:
		o<<*v.sc;
		break;
	case typTEXT:
		o<<*v.txt;
		break;
	case typINTEGER:
		o<<*v.intgr;
		break;
	case typDOUBLE:
		o<<*v.dbl;
		break;
	}
	return o;
}
istream& operator>>(istream& i,SMADVARIANT& v){
	switch(v.type){
	case typSMALLCHAR:
		i>>*v.sc;
		break;
	case typTEXT:
		i>>*v.txt;
		break;
	case typINTEGER:
		i>>*v.intgr;
		break;
	case typDOUBLE:
		i>>*v.dbl;
		break;
	}
	return i;
}

*/
#endif
	