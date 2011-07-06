#include "glblinc.h"

/*
#include <iostream>
#include <string>
using namespace std;

#include "variant.h"
#include "text.h"
#include "smallchar.h"
#include "double.h"
#include "integer.h"
*/

SMADVARIANT::~SMADVARIANT(){
	switch(type){
	case typSMALLCHAR:
		delete sc;
		break;
	case typTEXT:
		delete txt;
		break;
	case typDOUBLE:
		delete dbl;
		break;
	case typINTEGER:
		delete intgr;
		break;
	default:;
	}
}

SMADVARIANT::SMADVARIANT(const SMADVARIANT& v){
	switch(v.type){
	case typSMALLCHAR:
		sc=new SMADSMALLCHAR(*v.sc);
		type=typSMALLCHAR;
		break;
	case typDOUBLE:
		dbl=new SMADDOUBLE(*v.dbl);
		type=typDOUBLE;
		break;
	case typINTEGER:
		intgr=new SMADINTEGER(*v.intgr);
		type=typINTEGER;
		break;
	case typTEXT:
		txt=new SMADTEXT(*v.txt);
		type=typTEXT;
		break;
	}

}

bool operator<( const SMADVARIANT& v1, const SMADVARIANT& v2){
	switch(v1.type){
	case typINTEGER:
		return *v1.intgr<*v2.intgr;
	case typDOUBLE:
		return *v1.dbl<*v2.dbl;
	case typTEXT:
		return *v1.txt<*v2.txt;
	case typSMALLCHAR:
		return *v1.sc<*v2.sc;
	}
}

bool operator>(const SMADVARIANT& v1, const SMADVARIANT& v2){
	switch(v1.type){
	case typINTEGER:
		return *v1.intgr>*v2.intgr;
	case typDOUBLE:
		return *v1.dbl>*v2.dbl;
	case typTEXT:
		return *v1.txt>*v2.txt;
	case typSMALLCHAR:
		return *v1.sc>*v2.sc;
	}
}

SMADVARIANT& SMADVARIANT::operator+=( SMADTEXT& t){
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
SMADVARIANT& SMADVARIANT::operator+=( SMADDOUBLE& d){
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
SMADVARIANT& SMADVARIANT::operator+=( SMADINTEGER& i){
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
SMADVARIANT& SMADVARIANT::operator+=( SMADSMALLCHAR& sm){
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
	
		


int SMADVARIANT::serialize(smadfiler& o){
	int result;
		switch (type){
		case typSMALLCHAR:
			result=sc->serialize(o);
			break;
		case typTEXT:
			result=txt->serialize(o);
			break;
		case typINTEGER:
			result=intgr->serialize(o);
			break;
		case typDOUBLE:
			int result=dbl->serialize(o);
			break;
		}
		return result;

}
int SMADVARIANT::deserialize(smadfiler& i){
	int result;

		switch(type){
		case typSMALLCHAR: 
			result=sc->deserialize(i);
			break;
		case typTEXT:
			result=txt->deserialize(i);
			break;
		case typINTEGER:
			result=intgr->deserialize(i);
			break;
		case typDOUBLE:
			result=dbl->deserialize(i);
			break;
		}
		return result;

}
SMADVARIANT::SMADVARIANT(SMADSMALLCHAR* psc){
		put_data(psc);
		dbl=NULL;
		intgr=NULL;
		txt=NULL;
	}

SMADVARIANT::SMADVARIANT(SMADTEXT* ptxt){
		put_data(ptxt);
		dbl=NULL;
		intgr=NULL;
		sc=NULL;
	}

SMADVARIANT::SMADVARIANT(SMADINTEGER* pint){
		put_data(pint);
		dbl=NULL;
		sc=NULL;
		txt=NULL;
	}
SMADVARIANT::SMADVARIANT(SMADDOUBLE* pdbl){
		put_data(pdbl);
		sc=NULL;
		intgr=NULL;
		txt=NULL;
	}

void SMADVARIANT::set_type(enum fld_typ t){
		type=t;
}
enum fld_typ SMADVARIANT::get_type()const{
		return type;
}

SMADVARIANT::SMADVARIANT():type(typVARIANT){
		dbl=NULL;
		intgr=NULL;
		txt=NULL;
		sc=NULL;

}
SMADVARIANT& SMADVARIANT::operator=(SMADSMALLCHAR* psc){
		put_data(psc);
		dbl=NULL;
		intgr=NULL;
		txt=NULL;
        return *this;

}

SMADVARIANT& SMADVARIANT::operator=(SMADTEXT* ptxt){
		put_data(ptxt);
		dbl=NULL;
		intgr=NULL;
		sc=NULL;
		return *this;

}

SMADVARIANT& SMADVARIANT::operator=(SMADINTEGER* pint){
		put_data(pint);
		dbl=NULL;
		sc=NULL;
		txt=NULL;
		return *this;

}
SMADVARIANT& SMADVARIANT::operator=(SMADDOUBLE* pdbl){
		put_data(pdbl);
		sc=NULL;
		intgr=NULL;
		txt=NULL;
		return *this;

}


SMADVARIANT& SMADVARIANT::operator=(const SMADVARIANT& v){
	switch(v.type){
	case typSMALLCHAR:
		sc=new SMADSMALLCHAR(*v.sc);
		type=typSMALLCHAR;
		break;
	case typDOUBLE:
		dbl=new SMADDOUBLE(*v.dbl);
		type=typDOUBLE;
		break;
	case typINTEGER:
		intgr=new SMADINTEGER(*v.intgr);
		type=typINTEGER;
		break;
	case typTEXT:
		txt=new SMADTEXT(*v.txt);
		type=typTEXT;
		break;
	}
	return *this;



	/*
	if (type==typVARIANT)
		type=v.type;
		switch (type){
		case typINTEGER:
			intgr=&(SMADINTEGER)v;
			//intgr=&(v.toINTEGER());
			break;
		case typDOUBLE:
			dbl=&(SMADDOUBLE)v;
			//dbl=&(v.toDOUBLE());
			break;
		case typTEXT:
			txt=&(SMADTEXT)v;
			//txt=&(v.toTEXT());
			break;
		case typSMALLCHAR:
			//sc=&(v.toSMALLCHAR());
			sc=&(SMADSMALLCHAR)v;
			break;
		}
		return *this;
*/
}

	

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
			return (SMADDOUBLE)*intgr;
			break;
		case typTEXT:
			return (SMADDOUBLE)*txt;
			break;
		case typSMALLCHAR:
			return (SMADDOUBLE)*sc;
			break;
		}
		return *dbl;
	}

	SMADINTEGER SMADVARIANT::toINTEGER(){
		switch (type){
		case typDOUBLE:
			return (SMADINTEGER)*dbl;
			break;

		case typTEXT:
			return (SMADINTEGER)*txt;
			break;

		case typSMALLCHAR:
			return (SMADINTEGER)*sc;
			break;

		}
		return *intgr;

	}

	SMADTEXT SMADVARIANT::toTEXT(){
		switch (type){
		case typSMALLCHAR:
			return (SMADTEXT)*sc;
		case typINTEGER:
			return (SMADTEXT)*intgr;
		case typDOUBLE:
			return (SMADTEXT)*dbl;
		}
		return *txt;

	}
	SMADSMALLCHAR SMADVARIANT::toSMALLCHAR(){
		switch (type){
		case typTEXT:
			return (SMADSMALLCHAR)*txt;
		case typINTEGER:
			return (SMADSMALLCHAR)*intgr;
		case typDOUBLE:
			return (SMADSMALLCHAR)*dbl;
		}
		return *sc;

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


