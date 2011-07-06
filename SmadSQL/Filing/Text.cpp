#include "glblinc.h"

/*
#include <iostream>
#include <string>
using namespace std;

#include "SMADDOUBLE.h"

#include "SMADINTEGER.h"

#include "Text.h"
#include "smallchar.h"

#include "variant.h"
*/


const int MAXTEXT = 4096;



    SMADTEXT::SMADTEXT()/*:size(0)*/{}
	SMADTEXT::SMADTEXT(const string& s){
		/*
		data.assign(s,0,
			s.length()>MAXTEXT?MAXTEXT
			:s.length());
		size=s.length()>MAXTEXT?MAXTEXT:
		     s.length();
			 */
		data=s;
		data.resize(MAXTEXT);

		}
	SMADTEXT::SMADTEXT (const char* s){
		/*
		data.assign(s, strlen(s)()>MAXTEXT?
        MAXTEXT:strlen(s));
		size=strlen(s)>MAXTEXT?MAXTEXT:
		     strlen(s);
			 */
		data=s;
		data.resize(MAXTEXT);

		}
	SMADTEXT& SMADTEXT::operator=(const SMADTEXT& t){
		data=t.data;
		//size=t.length();
		return *this;

		}
	SMADTEXT& SMADTEXT::operator=(const string& s){
		/*
		data.assign(s,0,
			s.length()>MAXTEXT?
            MAXTEXT:s.length());
		size=s.length()>MAXTEXT?MAXTEXT:
		     s.length();
			 */
		data=s;
		data.resize(MAXTEXT);

	    return *this;
		}
    SMADTEXT& SMADTEXT::operator=(const char* s){
		/*
		data.assign(s,
			strlen(s)>MAXTEXT?MAXTEXT:
		    strlen(s);
        size=strlen(s)>MAXTEXT?MAXTEXT:
		     strlen(s);
			 */
		data=s;
		data.resize(MAXTEXT);

		return *this;
		}
	int SMADTEXT::serialize(smadfiler& o){
		data.resize(MAXTEXT);

		int result = o.write((char*)data.c_str(),data.length()+1);
		/*
		for(int i=size;i<=MAXTEXT;i++){
			o.put(0);
			}*/

		return result;

		}
	int SMADTEXT::deserialize(smadfiler& i){
		//char ch;
		for(int j=0;j<=MAXTEXT;j++)
			data+=i.getbyte();
		//size=data.length();
/*
		for(j=data.length();j<=MAXTEXT;j++){
			data+=(char)0;

			}
			*/
		return (int)0;
		}

	//CONVERSION FUNCTIONS

	SMADTEXT::operator SMADDOUBLE(){
		SMADDOUBLE d(atof(data.c_str()));
		return d;
		}
	SMADTEXT::operator SMADINTEGER(){
		SMADINTEGER i(atol(data.c_str()));
		return i;
		}
	SMADTEXT::operator long(){
		return atol(data.c_str());
	}
	SMADTEXT::operator  double(){
		return atof(data.c_str());
	}

	SMADTEXT::operator string(){
		return data;
	}
	SMADTEXT::operator char*(){
		return const_cast<char*>(data.c_str());
	}
	SMADTEXT::operator SMADSMALLCHAR(){
		return SMADSMALLCHAR(data);
	}
	SMADTEXT::operator SMADVARIANT(){
		return SMADVARIANT(this);
	}



	SMADTEXT SMADTEXT::operator+(const SMADTEXT& t){
		SMADTEXT aux;
		/*
		string aux_str;
		aux_str=data+t.data;
		aux.data.assign(aux_str,0,
			aux_str.length()>MAXTEXT?MAXTEXT:aux_str.length());
		aux.size=aux.data.length();
		*/
		aux.data=data+t.data;
		aux.data.resize(MAXTEXT);

		return aux;
		}
	SMADTEXT SMADTEXT::operator+(const string& s){
		SMADTEXT aux;
		/*
		string aux_str;
		aux.data.assign(data+s,0,
			(data+s).length()>MAXTEXT?
			MAXTEXT:(data+s).length());
		aux.size=aux.data.length();
		*/
		aux.data=data+s;
		aux.data.resize(MAXTEXT);

		return aux;

		}
	SMADTEXT SMADTEXT::operator+(const char* s){
		SMADTEXT aux;
		aux.data=data+s;
		aux.data.resize(MAXTEXT);
		return aux;


		}
	SMADTEXT& SMADTEXT::operator+=(const SMADTEXT& t){
		data+=t.data;
		data.resize(MAXTEXT);
		return *this;

		}
	SMADTEXT& SMADTEXT::operator+=(const string& s){
		data+=s;
		data.resize(MAXTEXT);
		return *this;
		}
	SMADTEXT& SMADTEXT::operator+=(const char* s){
		data+=s;
		data.resize(MAXTEXT);
		return *this;

		}
	const string& SMADTEXT::value()const {
		return data;
		}
	const char* SMADTEXT::value(char* s)const {
		//data.copy(s,data.length());
		return data.c_str();//s;
		}

	const string& SMADTEXT::setvalue(const string& new_val){
		data=new_val;
		data.resize(MAXTEXT);
		return data;//const_cast<string&>(new_val);

		}
	const char* SMADTEXT::setvalue(const char* new_val){
		data=new_val;
		data.resize(MAXTEXT);
		return data.c_str();//const_cast<char*>(new_val);

		}

	ostream& operator<<(ostream& o, const SMADTEXT& t){
		o<<t.data;
		return o;
		}
	istream& operator>>(istream& i,SMADTEXT& t){
		i>>t.data;
		return i;
		}


	SMADTEXT operator+(const char* s,
		const SMADTEXT& ob){
		SMADTEXT aux;
		aux.data=s+ob.data;
		aux.data.resize(MAXTEXT);
		return aux;
		}
	SMADTEXT operator+(const string& s,
		const SMADTEXT& ob){
		SMADTEXT aux;
		aux.data=s+ob.data;
		aux.data.resize(MAXTEXT);
		return aux;
		}
	bool operator<(const SMADTEXT& lhs, const SMADTEXT& rhs){
		return lhs.data<rhs.data;
		}
	
	bool operator<(const SMADTEXT& lhs, const string& rhs){
		return lhs.data<rhs;
		}

	bool operator<(const string& lhs,const SMADTEXT& rhs){

		return lhs<rhs.data;
		}

	bool operator<(const SMADTEXT& lhs, const char* rhs){
		return lhs.data<rhs;
		}


    bool operator<(const char* lhs, const SMADTEXT& rhs){
		return lhs< rhs.data;
		}

	bool operator>(const SMADTEXT& lhs, const SMADTEXT& rhs){
		return lhs.data>rhs.data;
		}
	
	bool operator>(const SMADTEXT& lhs, const string& rhs){
		return lhs.data>rhs;
		}

	bool operator>(const string& lhs,const SMADTEXT& rhs){

		return lhs>rhs.data;
		}

	bool operator>(const SMADTEXT& lhs, const char* rhs){
		return lhs.data>rhs;
		}


	bool operator>(const char* lhs, const SMADTEXT& rhs){
		return lhs>rhs.data;
		}

	bool operator<=(const SMADTEXT& lhs, const SMADTEXT& rhs){
		return lhs.data<=rhs.data;
		}
	
	bool operator<=(const SMADTEXT& lhs, const string& rhs){
		return lhs.data<=rhs;
		}

	bool operator<=(const string& lhs,const SMADTEXT& rhs){

		return lhs<=rhs.data;
		}

	bool operator<=(const SMADTEXT& lhs, const char* rhs){
		return lhs.data<=rhs;
		}


	bool operator<=(const char* lhs, const SMADTEXT& rhs){
		return lhs<=rhs.data;
		}

	bool operator>=(const SMADTEXT& lhs, const SMADTEXT& rhs){
		return lhs.data>=rhs.data;
		}
	
	bool operator>=(const SMADTEXT& lhs, const string& rhs){
		return lhs.data>=rhs;
		}

	bool operator>=(const string& lhs,const SMADTEXT& rhs){

		return lhs>=rhs.data;
		}

	bool operator>=(const SMADTEXT& lhs, const char* rhs){
		return lhs.data>=rhs;
		}


	bool operator>=(const char* lhs, const SMADTEXT& rhs){
		return lhs>=rhs.data;
		}
	bool operator==(const SMADTEXT& lhs, const SMADTEXT& rhs){
		return lhs.data==rhs.data;
		}
	
	bool operator==(const SMADTEXT& lhs, const string& rhs){
		return lhs.data==rhs;
		}

	bool operator==(const string& lhs,const SMADTEXT& rhs){

		return lhs==rhs.data;
		}

	bool operator==(const SMADTEXT& lhs, const char* rhs){
		return lhs.data==rhs;
		}


	bool operator==(const char* lhs, const SMADTEXT& rhs){
		return lhs==rhs.data;
		}
	
	bool operator!=(const SMADTEXT& lhs, const SMADTEXT& rhs){
		return lhs.data!=rhs.data;
		}
	
	bool operator!=(const SMADTEXT& lhs, const string& rhs){
		return lhs.data!=rhs;
		}

	bool operator!=(const string& lhs,const SMADTEXT& rhs){

		return lhs!=rhs.data;
		}

	bool operator!=(const SMADTEXT& lhs, const char* rhs){
		return lhs.data!=rhs;
		}


	bool operator!=(const char* lhs, const SMADTEXT& rhs){
		return lhs!=rhs.data;
		}
