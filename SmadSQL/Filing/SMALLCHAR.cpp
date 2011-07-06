/*
#include <iostream>
#include <string>
using namespace std;

#include "SMADSMALLCHAR.h"
#include "text.h"
#include "SMADDOUBLE.h"
#include "SMADINTEGER.h"

#include "variant.h"
*/
#include "glblinc.h"

const int MAXSMALLCHAR=255;


    SMADSMALLCHAR::SMADSMALLCHAR()/*:size(0)*/{}
	SMADSMALLCHAR::SMADSMALLCHAR(const string& s){
		/*
		data.assign(s,0,
			s.length()>MAXSMALLCHAR?MAXSMALLCHAR
			:s.length());
		size=s.length()>MAXSMALLCHAR?MAXSMALLCHAR:
		     s.length();
			 */
		data=s;
		//truncate to max allowed length

		data.resize(MAXSMALLCHAR);

		}
	SMADSMALLCHAR::SMADSMALLCHAR (const char* s){
		/*
		data.assign(s, strlen(s)()>MAXSMALLCHAR?
        MAXSMALLCHAR:strlen(s));
		size=strlen(s)>MAXSMALLCHAR?MAXSMALLCHAR:
		     strlen(s);
			 */
		data=s;
        //truncate to max allowed length
		data.resize(MAXSMALLCHAR);

		}
	SMADSMALLCHAR::SMADSMALLCHAR (const SMADSMALLCHAR& ob){
		data=ob.data;

		}

	SMADSMALLCHAR& SMADSMALLCHAR::operator=(const SMADSMALLCHAR& t){
		data=t.data;
		//size=t.length();
		return *this;

		}
	SMADSMALLCHAR& SMADSMALLCHAR::operator=(const string& s){
		/*
		data.assign(s,0,
			s.length()>MAXSMALLCHAR?
            MAXSMALLCHAR:s.length());
		size=s.length()>MAXSMALLCHAR?MAXSMALLCHAR:
		     s.length();
			 */
		data=s;
		//truncate to max allowed length
		data.resize(MAXSMALLCHAR);

	    return *this;
		}
    SMADSMALLCHAR& SMADSMALLCHAR::operator=(const char* s){
		/*
		data.assign(s,
			strlen(s)>MAXSMALLCHAR?MAXSMALLCHAR:
		    strlen(s);
        size=strlen(s)>MAXSMALLCHAR?MAXSMALLCHAR:
		     strlen(s);
			 */
		data=s;
		//truncate to max allowed length
		data.resize(MAXSMALLCHAR);

		return *this;
		}
	SMADSMALLCHAR& SMADSMALLCHAR::operator=(const SMADTEXT& t){
		data=t.value();
		data.resize(MAXSMALLCHAR);
		return *this;
		}


	//CONVERSION FUNCTIONS
	SMADSMALLCHAR::operator SMADDOUBLE(){
		SMADDOUBLE ret_val(atof(data.c_str()));
		return ret_val;
		}   
	SMADSMALLCHAR::operator SMADINTEGER(){
		SMADINTEGER ret_val(atol(data.c_str()));
		return ret_val;
		}
	SMADSMALLCHAR::operator SMADTEXT(){
		SMADTEXT ret_val=data;
		return ret_val;
		}
	
	SMADSMALLCHAR::operator char*(){
		return const_cast<char*>(data.c_str());
		}
	SMADSMALLCHAR::operator string(){
		return data;

		}
	SMADSMALLCHAR::operator  long(){
		return atol(data.c_str());
	}
	SMADSMALLCHAR::operator double(){
		return atof(data.c_str());
	}
	SMADSMALLCHAR::operator SMADVARIANT(){
		return SMADVARIANT(this);
	}



	int SMADSMALLCHAR::serialize(smadfiler& o){
		/*make the string's length
		maximum bcz we r doing fixed 
		length fields
		*/

		data.resize(MAXSMALLCHAR);

		int result = o.write((char*)data.c_str(),data.length()+1);
		//for(int i=data.length();
		/*
		for(int i=size;i<=MAXSMALLCHAR;i++){
			o.put(0);
			}*/

		return result;

		}
	int SMADSMALLCHAR::deserialize(smadfiler& i){
		//char ch;
		for(int j=0;j<=MAXSMALLCHAR;j++)
			data+=(char)i.getbyte();
		//size=data.length();
		//read in the string until NULL is
		//encountered and then pad the 
		//rest with ZEROS
		//remember its a 255b field

/*
		for(j=data.length();j<=MAXSMALLCHAR;j++){
			data+=(char)0;
			}
			*/
		return 0;
		}

	SMADSMALLCHAR SMADSMALLCHAR::operator+(SMADSMALLCHAR t){
		SMADSMALLCHAR aux;
		/*
		string aux_str;
		aux_str=data+t.data;
		aux.data.assign(aux_str,0,
			aux_str.length()>MAXSMALLCHAR?MAXSMALLCHAR:aux_str.length());
		aux.size=aux.data.length();
		*/
		aux.data=data+t.data;
		//truncate to max allowed length
		aux.data.resize(MAXSMALLCHAR);

		return aux;
		}
	SMADSMALLCHAR SMADSMALLCHAR::operator+(const string& s){
		SMADSMALLCHAR aux;
	    /*
		string aux_str;
		aux.data.assign(data+s,0,
			(data+s).length()>MAXSMALLCHAR?
			MAXSMALLCHAR:(data+s).length());
		aux.size=aux.data.length();
		*/
		aux.data=data+s;
		//truncate to max allowed length
		aux.data.resize(MAXSMALLCHAR);

		return aux;

		}
	SMADSMALLCHAR SMADSMALLCHAR::operator+(const char* s){
		SMADSMALLCHAR aux;
		aux.data=data+s;
		aux.data.resize(MAXSMALLCHAR);
		return aux;

		}
	SMADSMALLCHAR SMADSMALLCHAR::operator+(SMADTEXT t){
		SMADSMALLCHAR aux;
		aux.data=t.value();
		aux.data.resize(MAXSMALLCHAR);
		return aux;
		}
	
	SMADSMALLCHAR& SMADSMALLCHAR::operator+=(SMADSMALLCHAR t){
		data+=t.data;
		data.resize(MAXSMALLCHAR);
		return *this;

		}
	SMADSMALLCHAR& SMADSMALLCHAR::operator+=(const string& s){
		data+=s;
		data.resize(MAXSMALLCHAR);
		return *this;
		}
	SMADSMALLCHAR& SMADSMALLCHAR::operator+=(const char* s){
		data+=s;
		data.resize(MAXSMALLCHAR);
		return *this;

		}
	SMADSMALLCHAR& SMADSMALLCHAR::operator+=(SMADTEXT t){
		data+=t.value();
		data.resize(MAXSMALLCHAR);
		return *this;
		}

	//return the data as a string

	const string& SMADSMALLCHAR::value() const {
		return data;
		}
	const char* SMADSMALLCHAR::value(char* s) const {
		data.copy(s,data.length());
		return s;
		}
	char* SMADSMALLCHAR::setvalue(const char* s){
		data=s;
		data.resize(MAXSMALLCHAR);

		return const_cast<char*>(s);
		}
	string SMADSMALLCHAR::setvalue(const string& s){
		data=s;
		data.resize(MAXSMALLCHAR);
		return s;
		}



		
	ostream& operator<<(ostream& o, const SMADSMALLCHAR& ob){
		o<<ob.data;
		return o;
		}
	istream& operator>>(istream& i, SMADSMALLCHAR& ob){
		i>>ob.data;
		return i;
		}

	SMADSMALLCHAR operator+(const char* s,
		SMADSMALLCHAR ob){
		SMADSMALLCHAR aux;
		aux.data=s+ob.data;
		aux.data.resize(MAXSMALLCHAR);
		return aux;
		}
	SMADSMALLCHAR operator+(const string& s,
		SMADSMALLCHAR ob){
		SMADSMALLCHAR aux;
		aux.data=ob.data+s;
		aux.data.resize(MAXSMALLCHAR);
		return aux;
		}
	bool operator<(const SMADSMALLCHAR& lhs, const SMADSMALLCHAR& rhs){
		return lhs.data<rhs.data;
		}
	
	bool operator<(const SMADSMALLCHAR& lhs, const string& rhs){
		return lhs.data<rhs;
		}

	bool operator<(const string& lhs,const SMADSMALLCHAR& rhs){

		return lhs<rhs.data;
		}

	bool operator<(const SMADSMALLCHAR& lhs, const char* rhs){
		return lhs.data<rhs;
		}


	bool operator<(const char* lhs, const SMADSMALLCHAR& rhs){
		return lhs< rhs.data;
		}

	bool operator>(const SMADSMALLCHAR& lhs, const SMADSMALLCHAR& rhs){
		return lhs.data>rhs.data;
		}
	
	bool operator>(const SMADSMALLCHAR& lhs, const string& rhs){
		return lhs.data>rhs;
		}

	bool operator>(const string& lhs,const SMADSMALLCHAR& rhs){

		return lhs>rhs.data;
		}

	bool operator>(const SMADSMALLCHAR& lhs, const char* rhs){
		return lhs.data>rhs;
		}


	bool operator>(const char* lhs, const SMADSMALLCHAR& rhs){
		return lhs>rhs.data;
		}

	bool operator<=(const SMADSMALLCHAR& lhs, const SMADSMALLCHAR& rhs){
		return lhs.data<=rhs.data;
		}
	
	bool operator<=(const SMADSMALLCHAR& lhs, const string& rhs){
		return lhs.data<=rhs;
		}

	bool operator<=(const string& lhs,const SMADSMALLCHAR& rhs){

		return lhs<=rhs.data;
		}

	bool operator<=(const SMADSMALLCHAR& lhs, const char* rhs){
		return lhs.data<=rhs;
		}


	bool operator<=(const char* lhs, const SMADSMALLCHAR& rhs){
		return lhs<=rhs.data;
		}

	bool operator>=(const SMADSMALLCHAR& lhs, const SMADSMALLCHAR& rhs){
		return lhs.data>=rhs.data;
		}
	
	bool operator>=(const SMADSMALLCHAR& lhs, const string& rhs){
		return lhs.data>=rhs;
		}

	bool operator>=(const string& lhs,const SMADSMALLCHAR& rhs){

		return lhs>=rhs.data;
		}

	bool operator>=(const SMADSMALLCHAR& lhs, const char* rhs){
		return lhs.data>=rhs;
		}


	bool operator>=(const char* lhs, const SMADSMALLCHAR& rhs){
		return lhs>=rhs.data;
		}
	bool operator==(const SMADSMALLCHAR& lhs, const SMADSMALLCHAR& rhs){
		return lhs.data==rhs.data;
		}
	
	bool operator==(const SMADSMALLCHAR& lhs, const string& rhs){
		return lhs.data==rhs;
		}

	bool operator==(const string& lhs,const SMADSMALLCHAR& rhs){

		return lhs==rhs.data;
		}

	bool operator==(const SMADSMALLCHAR& lhs, const char* rhs){
		return lhs.data==rhs;
		}


	bool operator==(const char* lhs, const SMADSMALLCHAR& rhs){
		return lhs==rhs.data;
		}
	
	bool operator!=(const SMADSMALLCHAR& lhs, const SMADSMALLCHAR& rhs){
		return lhs.data!=rhs.data;
		}
	
	bool operator!=(const SMADSMALLCHAR& lhs, const string& rhs){
		return lhs.data!=rhs;
		}

	bool operator!=(const string& lhs,const SMADSMALLCHAR& rhs){

		return lhs!=rhs.data;
		}

	bool operator!=(const SMADSMALLCHAR& lhs, const char* rhs){
		return lhs.data!=rhs;
		}


	bool operator!=(const char* lhs, const SMADSMALLCHAR& rhs){
		return lhs!=rhs.data;
		}
