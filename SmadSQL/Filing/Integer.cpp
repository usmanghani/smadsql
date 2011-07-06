/*
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#include "integer.h"
#include "double.h"
#include "smallchar.h"
#include "text.h"

#include "variant.h"

*/
#include "glblinc.h"

    SMADINTEGER::SMADINTEGER ():data(0){}
    SMADINTEGER::SMADINTEGER (long val){
		data=val;
		}
	SMADINTEGER::SMADINTEGER (const SMADINTEGER& ob){
		this->data=ob.data;
		}
	SMADINTEGER& SMADINTEGER::operator=(const SMADINTEGER& ob){
		this->data=ob.data;
		return *this;

		}
	//assign a long to SMADINTEGER

	SMADINTEGER& SMADINTEGER::operator=(long ob){
		data=ob;
		return *this;
		}
    // put raw bin data to stream
	
	int SMADINTEGER::serialize(smadfiler& o){
		int result=o.write((char*)&data, sizeof(data));
		return result;
		}
	//get raw bin data from stream

	int SMADINTEGER::deserialize(smadfiler& i){
		int result=i.read((char*)&data,sizeof(data));
		return result;
		}
	
	
    long SMADINTEGER::value(){
		return data;
		}
	long SMADINTEGER::setvalue(long l){
		data=l;
		return l;
		}


 	 SMADINTEGER::operator long(){
		 return data;
		 }
	 SMADINTEGER::operator double(){
		 return (double)data;
	 }
	 SMADINTEGER::operator SMADDOUBLE(){
		 return SMADDOUBLE ((double)data);
	 }
	 SMADINTEGER::operator string(){
		 char aux[12];
		 return string(ltoa(data,aux,10));
	 }
	 SMADINTEGER::operator SMADSMALLCHAR(){
		 char aux[12];
		 return SMADSMALLCHAR(ltoa(data,aux,10));
	 }
	 SMADINTEGER::operator SMADTEXT(){
		 char aux[12];
		 return SMADTEXT(ltoa(data,aux,10));
	 }
	 SMADINTEGER::operator SMADVARIANT(){
		 return SMADVARIANT(this);
	 }



	SMADINTEGER SMADINTEGER::operator+(SMADINTEGER ob){
		SMADINTEGER aux;

		aux.data=data+ob.data;
		return aux;
		}
	SMADINTEGER& SMADINTEGER::operator+=(SMADINTEGER ob){
		data+=ob.data;
		return *this;
		}
	 
	 SMADINTEGER SMADINTEGER::operator+(long l){
		 SMADINTEGER aux;
		 aux.data=data+l;
		 return aux;
		 }
	 SMADINTEGER& SMADINTEGER::operator+=(long l){
		 data+=l;
		 return *this;
		 }
	 SMADINTEGER SMADINTEGER::operator-(SMADINTEGER ob){
		/*
		 SMADINTEGER aux;
		 aux=data-ob.data;
		 return aux;
		 */
		 return SMADINTEGER(data-ob.data);

		 }
	 SMADINTEGER& SMADINTEGER::operator-=(SMADINTEGER ob){
		 data-=ob.data;
		 return *this;
		 }
	 SMADINTEGER SMADINTEGER::operator-(long l){
		 SMADINTEGER aux;
		 aux.data=data-l;
		 return aux;
		 }
	 SMADINTEGER& SMADINTEGER::operator-=(long l){
		 data-=l;
		 return *this;
		 }
	 SMADINTEGER& SMADINTEGER::operator++(){
		 ++data;
		 return *this;
		 }
	 SMADINTEGER& SMADINTEGER::operator++(int){
		 data++;
		 return *this;
		 }
	 SMADINTEGER& SMADINTEGER::operator--(){
		 --data;
		 return *this;
		 }
	 SMADINTEGER& SMADINTEGER::operator--(int){
		 data--;
		 return *this;
		 }
	 SMADINTEGER SMADINTEGER::operator*(SMADINTEGER ob){
		 SMADINTEGER aux;
		 aux=data*ob.data;
		 return aux;
		 }
	 SMADINTEGER& SMADINTEGER::operator*=(SMADINTEGER ob){
		 data*=ob.data;
		 return *this;
		 }
	 SMADINTEGER SMADINTEGER::operator*(long l){
		 SMADINTEGER aux;
		 aux.data=data*l;
		 return aux;
		 }
	 SMADINTEGER& SMADINTEGER::operator*=(long l){
		 data*=l;
		 return *this;
		 }

	 SMADINTEGER SMADINTEGER::operator/(SMADINTEGER ob){
		 SMADINTEGER aux;
		 aux.data=data/ob.data;
		 return aux;
		 }
	 SMADINTEGER& SMADINTEGER::operator/=(SMADINTEGER ob){
		 data/=ob.data;
		 return *this;
		 }
	 SMADINTEGER SMADINTEGER::operator/(long l){
		 SMADINTEGER aux;
	     aux.data=data/l;
		 return aux;
		 }
	 SMADINTEGER& SMADINTEGER::operator/=(long l){
		 data/=l;
		 return *this;
		 }
     SMADINTEGER SMADINTEGER::operator%(SMADINTEGER ob){
		 SMADINTEGER aux;
		 aux.data=data%ob.data;
		 return aux;
		 }
	 SMADINTEGER& SMADINTEGER::operator%=(SMADINTEGER ob){
		 data%=ob.data;
		 return *this;
		 }
	 SMADINTEGER SMADINTEGER::operator%(long l){
		 SMADINTEGER aux;
	     aux.data=data%l;
		 return aux;
		 }
	 SMADINTEGER& SMADINTEGER::operator%=(long l){
		 data%=l;
		 return *this;
		 }
	 //friend functions

	istream& operator>>(istream& i, SMADINTEGER& ob){
		i>>ob.data;
		return i;
		}
	ostream& operator<<(ostream& o,const SMADINTEGER& ob){
		o<<ob.data;
		return o;
		}
	
	

	 SMADINTEGER operator+(long lhs, const SMADINTEGER& rhs){
		 SMADINTEGER aux;
		 aux.data=lhs+rhs.data;
		 return aux;
		 }


	 SMADINTEGER operator-(long lhs, const SMADINTEGER& rhs){
		 SMADINTEGER aux;
		 aux.data=lhs-rhs.data;
		 return aux;
		 }

		 
	 SMADINTEGER operator/(long lhs, const SMADINTEGER& rhs){
		 SMADINTEGER aux;
		 aux.data=lhs/rhs.data;
		 return aux;
		 }

		 
	 SMADINTEGER operator*(long lhs, const SMADINTEGER& rhs){
		 SMADINTEGER aux;
		 aux.data=lhs*rhs.data;
		 return aux;
		 
		 }


	 SMADINTEGER operator%(long lhs, const SMADINTEGER& rhs){
		 SMADINTEGER aux;
		 aux.data=lhs%rhs.data;
		 return aux;
		 }
		 
     bool operator<(const SMADINTEGER& lhs, const SMADINTEGER& rhs){
		 return lhs.data<rhs.data;
		 }


	 bool operator<(const SMADINTEGER& lhs, const long rhs){
		 return lhs.data<rhs;
		 }

	 bool operator<(const long lhs, const SMADINTEGER& rhs){
		 return lhs<rhs.data;
		 }


	 bool operator>(const SMADINTEGER& lhs, const SMADINTEGER& rhs){
		 return lhs.data>rhs.data;
		 }

	 bool operator>(const SMADINTEGER& lhs, const long rhs){
		 return lhs.data>rhs;
		 }

	 bool operator>(const long lhs, const SMADINTEGER& rhs){
		 return lhs>rhs.data;
		 }


	 bool operator<=(const SMADINTEGER& lhs, const SMADINTEGER& rhs){
		 return lhs.data<=rhs.data;
		 }

	 bool operator<=(const SMADINTEGER& lhs, const long rhs){
		 return lhs.data<=rhs;
		 }

	 bool operator<=(const long lhs, const SMADINTEGER& rhs){
		 return lhs<=rhs.data;
		 }


	 bool operator>=(const SMADINTEGER& lhs, const SMADINTEGER& rhs){
		 return lhs.data>=rhs.data;
		 }

	 bool operator>=(const SMADINTEGER& lhs, const long rhs){
		 return lhs.data>=rhs;
		 }

	 bool operator>=(const long lhs, const SMADINTEGER& rhs){
		 return lhs>=rhs.data;
		 }

	 bool operator!=(const SMADINTEGER& lhs, const SMADINTEGER& rhs){
		 return lhs.data!=rhs.data;
		 }

	 bool operator!=(const SMADINTEGER& lhs, const long rhs){
		 return lhs.data!=rhs;
		 }

	 bool operator!=(const long lhs, const SMADINTEGER& rhs){
		 return lhs!=rhs.data;
		 }

	 bool operator==(const SMADINTEGER& lhs, const SMADINTEGER& rhs){
		 return lhs.data>=rhs.data;
		 }

	 bool operator==(const SMADINTEGER& lhs, const long rhs){
		 return lhs.data>=rhs;
		 }

	 bool operator==(const long lhs, const SMADINTEGER& rhs){
		 return lhs>=rhs.data;
		 }

