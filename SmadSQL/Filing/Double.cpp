/*
#include <iostream>
#include <string>
#include <cstdlib> 
#include <cmath>


using namespace std;

#include "SMADDOUBLE.h"
#include "SMADTEXT.h"
#include "integer.h"
#include "smallchar.h"
#include "variant.h"

*/
#include "glblinc.h"

    SMADDOUBLE::SMADDOUBLE():data(0.0){}
	SMADDOUBLE::SMADDOUBLE(const SMADDOUBLE& ob){
		data=ob.data;
		}
	SMADDOUBLE::SMADDOUBLE(const double d){
		data=d;
		}

	SMADDOUBLE& SMADDOUBLE::operator=(const SMADDOUBLE& ob){
		data=ob.data;
		return *this;

		}
	SMADDOUBLE& SMADDOUBLE::operator=(const double d){
		data=d;
		return *this;

		}
	int SMADDOUBLE::serialize(smadfiler& o){
		int result=o.write((char*)&data, sizeof(data));
		return result;
		}
	//get raw bin data from stream

	int SMADDOUBLE::deserialize(smadfiler& i){
		int result=i.read((char*)&data,sizeof(data));
		return result;
		}
    double SMADDOUBLE::value() const{
		return data;
		}
	double SMADDOUBLE::setvalue(double d){
        data=d;
		return data;
		}

	 SMADDOUBLE::operator double(){
		 return data;
		 }
	 SMADDOUBLE::operator long(){
		 double d;
		 modf(data,&d);
		 return (long)d;
	 }
	 SMADDOUBLE::operator SMADINTEGER(){
		 double d;
		 modf(data,&d);
		 return SMADINTEGER((long)d);
	 }
	 SMADDOUBLE::operator string(){
		 char aux[25];
		 gcvt(data,5,aux);
		 return string(aux);
	 }
	 SMADDOUBLE::operator SMADSMALLCHAR(){
		 char aux[25];
		 gcvt(data,5,aux);
		 return SMADSMALLCHAR(aux);
	 }
	 SMADDOUBLE::operator SMADTEXT(){
		 char aux[25];

		 gcvt(data,5,aux);
		 return SMADTEXT(aux);
	 }
	 SMADDOUBLE::operator SMADVARIANT(){
		 return SMADVARIANT(this);
	 }
	 

	SMADDOUBLE SMADDOUBLE::operator+(const SMADDOUBLE& ob){
		SMADDOUBLE aux;

		aux.data=data+ob.data;
		return aux;
		}
	SMADDOUBLE& SMADDOUBLE::operator+=(const SMADDOUBLE& ob){
		data+=ob.data;
		return *this;
		}

	 SMADDOUBLE SMADDOUBLE::operator+(double l){
		 SMADDOUBLE aux;
		 aux.data=data+l;
		 return aux;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator+=(double l){
		 data+=l;
		 return *this;
		 }
	 SMADDOUBLE SMADDOUBLE::operator-(const SMADDOUBLE& ob){
		 SMADDOUBLE aux;
		 aux=data-ob.data;
		 return aux;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator-=(const SMADDOUBLE& ob){
		 data-=ob.data;
		 return *this;
		 }
	 SMADDOUBLE SMADDOUBLE::operator-(double l){
		 SMADDOUBLE aux;
		 aux.data=data-l;
		 return aux;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator-=(double l){
		 data-=l;
		 return *this;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator++(){
		 ++data;
		 return *this;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator++(int){
		 data++;
		 return *this;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator--(){
		 --data;
		 return *this;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator--(int){
		 data--;
		 return *this;
		 }
	 SMADDOUBLE SMADDOUBLE::operator*(const SMADDOUBLE& ob){
		 SMADDOUBLE aux;
		 aux=data*ob.data;
		 return aux;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator*=(const SMADDOUBLE& ob){
		 data*=ob.data;
		 return *this;
		 }
	 SMADDOUBLE SMADDOUBLE::operator*(double l){
		 SMADDOUBLE aux;
		 aux.data=data*l;
		 return aux;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator*=(double l){
		 data*=l;
		 return *this;
		 }

	 SMADDOUBLE SMADDOUBLE::operator/(const SMADDOUBLE& ob){
		 SMADDOUBLE aux;
		 aux.data=data/ob.data;
		 return aux;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator/=(const SMADDOUBLE& ob){
		 data/=ob.data;
		 return *this;
		 }
	 SMADDOUBLE SMADDOUBLE::operator/(double l){
		 SMADDOUBLE aux;
	     aux.data=data/l;
		 return aux;
		 }
	 SMADDOUBLE& SMADDOUBLE::operator/=(double l){
		 data/=l;
		 return *this;
		 }
	ostream& operator<<(ostream& o, const SMADDOUBLE& d){
		o<<d.data;
		return o;
		}
	istream& operator>>(istream& i, SMADDOUBLE& d){
		i>>d.data;
		return i;
		}



	 SMADDOUBLE operator+(double lhs, const SMADDOUBLE& rhs){
		 SMADDOUBLE aux;
		 aux.data=lhs+rhs.data;
		 return aux;
		 }


	 SMADDOUBLE operator-(double lhs, const SMADDOUBLE& rhs){
		 SMADDOUBLE aux;
		 aux.data=lhs-rhs.data;
		 return aux;
		 }

		 
	 SMADDOUBLE operator/(double lhs, const SMADDOUBLE& rhs){
		 SMADDOUBLE aux;
		 aux.data=lhs/rhs.data;
		 return aux;
		 }

		 
	 SMADDOUBLE operator*(double lhs, const SMADDOUBLE& rhs){
		 SMADDOUBLE aux;
		 aux.data=lhs*rhs.data;
		 return aux;
		 
		 }


	 
		 
     bool operator<(const SMADDOUBLE& lhs, const SMADDOUBLE& rhs){
		 return lhs.data<rhs.data;
		 }


	 bool operator<(const SMADDOUBLE& lhs, const double rhs){
		 return lhs.data<rhs;
		 }

	 bool operator<(const double lhs, const SMADDOUBLE& rhs){
		 return lhs<rhs.data;
		 }


	 bool operator>(const SMADDOUBLE& lhs, const SMADDOUBLE& rhs){
		 return lhs.data>rhs.data;
		 }

	 bool operator>(const SMADDOUBLE& lhs, const double rhs){
		 return lhs.data>rhs;
		 }

	 bool operator>(const double lhs, const SMADDOUBLE& rhs){
		 return lhs>rhs.data;
		 }


	 bool operator<=(const SMADDOUBLE& lhs, const SMADDOUBLE& rhs){
		 return lhs.data<=rhs.data;
		 }

	 bool operator<=(const SMADDOUBLE& lhs, const double rhs){
		 return lhs.data<=rhs;
		 }

	 bool operator<=(const double lhs, const SMADDOUBLE& rhs){
		 return lhs<=rhs.data;
		 }


	 bool operator>=(const SMADDOUBLE& lhs, const SMADDOUBLE& rhs){
		 return lhs.data>=rhs.data;
		 }

	 bool operator>=(const SMADDOUBLE& lhs, const double rhs){
		 return lhs.data>=rhs;
		 }

	 bool operator>=(const double lhs, const SMADDOUBLE& rhs){
		 return lhs>=rhs.data;
		 }

	 bool operator!=(const SMADDOUBLE& lhs, const SMADDOUBLE& rhs){
		 return lhs.data!=rhs.data;
		 }

	 bool operator!=(const SMADDOUBLE& lhs, const double rhs){
		 return lhs.data!=rhs;
		 }

	 bool operator!=(const double lhs, const SMADDOUBLE& rhs){
		 return lhs!=rhs.data;
		 }

	 bool operator==(const SMADDOUBLE& lhs, const SMADDOUBLE& rhs){
		 return lhs.data>=rhs.data;
		 }

	 bool operator==(const SMADDOUBLE& lhs, const double rhs){
		 return lhs.data>=rhs;
		 }

	 bool operator==(const double lhs, const SMADDOUBLE& rhs){
		 return lhs>=rhs.data;
		 }

