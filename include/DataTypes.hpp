/*
copyright: Faisal Nasim
           Usman Ghani
Author: Usman Ghani
    SMAD SQL data types
	  AND
	core objects


*/

//The SMALLCHAR data type
/*I have replaced this with a neater better
version
see below this

class SMALLCHAR{
private:
   //value is stored here
	char data[256];
	const int MAXSIZE=255;

public:
	SMALLCHAR(){
		for(int i=0;i<256;i++) data[i]=0;
		}
	SMALLCHAR(const string& s){
		this();
		
		strncpy(data,s.c_str(),
			s.length()>255?255:s.length());

		s.length()>255?data[255]=0
			:data[s.length()]=0;
		
         strncat(data,s.c_str(),255);
		 data[255]=0;
		 			
		}

	SMALLCHAR (const SMALLCHAR& ob){
		strcpy(data,ob.data);
		
		}
	SMALLCHAR (const char* s){
		strncpy(data,s,
			(strlen(s)>MAXSIZE)?MAXSIZE:
		    strlen(s));
		data[255]=0;

	
		}



    SMALLCHAR operator=(SMALLCHAR ob){
		strcpy(data,ob.data);
		return *this;

		}
	//asigns a string to SMALLCHAR
	SMALLCHAR operator=(string s){
		strcpy(data,s.c_str());
		return *this;
		}
	//assigns a C style string to SMALLCHAR 
    SMALLCHAR operator=(char* s){
		strcpy(data,s);
		return *this;
		}
	// returns the value of the SMALLCHAR
	// as a string
	string value(){
		string aux;
		char* ch=data;
		while(*ch) aux+=ch++;
		return aux;
		}
    // returns the value of the SMALLCHAR 
	// in s as a C style string

	char* value(char* s){
		
		strcpy(s,data);
		return s;
		}
    
    // put raw bin data in the stream
	ostream& serialize(ostream& o){
		o.write(data, sizeof(data));
		return o;

		}
	//get raw bin data from stream

	istream& deserialize(istream& i){
		i.read(data,sizeof(data));
		return i;
		}
    // put formatted data in text mode
	//stream. might be used for output

	ostream& operator<<(ostream& o){
		o<<data;
		return o;
		}
	//get formatted data from text mode stream
	//might be used for input

	istream& operator>>(istream& i){
		i>>data;

		return i;

		}
	SMALLCHAR operator+(SMALLCHAR ob){
		SMALLCHAR aux;
		//string s=data;
		s+=ob.data;
		//if the length is greater than 
		//255, truncate the string
		
		if(s.length()>255) {
			s.erase(255,s,length()-255);
			}
		strcpy(aux.data,s.c_str());
		return aux;
		//truncate the string if
		//its larger than 255

        strcpy(aux.data,data);
		strncat(aux.data,ob.data,
			strlen(data)+strlen(ob.data)
			<=255?strlen(ob.data):
		    255-strlen(data));
		return aux;

		}

	SMALLCHAR operator+=(SMALLCHAR ob){
		strncat(data, ob.data, 
			strlen(data)+strlen(ob.data)
			<=255?strlen(ob.data):
		    255-strlen(data));

		return *this;
		}
	 operator char*()(){
		 return data;
		 }
	 operator string()(){
		 string s(data);
		 return s;
		 }

	 SMALLCHAR operator+(char* s){
		 SMALLCHAR aux;
		 strcpy(aux.data,data);
		 strncat(aux.data,s,
			 strlen(data)+strlen(s)>255?
			 255-strlen(data):strlen(s));


		 return aux;
		 }
	 SMALLCHAR operator+(string s){
		 SMALLCHAR aux;
		 strcpy(aux.data,data);
		 strncat(aux.data,s.c_str(),
			 strlen(data)+s.length()>255?
			 255-strlen(data):s.length());
		 return aux;
		 }
	 SMALLCHAR operator+=(string s){
		 strncat(data,s.c_str(),
			 strlen(data)+s.length()>255?
			 255-strlen(data):
		     s.length());
		return *this;
		 }     
	};
*/


/*
This is the new string based implementation
of the SMALLCHAR data type
*/

class SMALLCHAR {
private:
	string data;
	//int size;
	const int MAXSIZE=255;


public:
	SMALLCHAR()/*:size(0)*/{}
	SMALLCHAR(const string& s){
		/*
		data.assign(s,0,
			s.length()>MAXSIZE?MAXSIZE
			:s.length());
		size=s.length()>MAXSIZE?MAXSIZE:
		     s.length();
			 */
		data=s;
		//truncate to max allowed length

		data.resize(MAXSIZE);

		}
	SMALLCHAR (const char* s){
		/*
		data.assign(s, strlen(s)()>MAXSIZE?
        MAXSIZE:strlen(s));
		size=strlen(s)>MAXSIZE?MAXSIZE:
		     strlen(s);
			 */
		data=s;
        //truncate to max allowed length
		data.resize(MAXSIZE);

		}
	SMALLCHAR& operator=(const SMALLCHAR& t){
		data=t;
		//size=t.length();
		return *this;

		}
	SMALLCHAR& operator=(const string& s){
		/*
		data.assign(s,0,
			s.length()>MAXSIZE?
            MAXSIZE:s.length());
		size=s.length()>MAXSIZE?MAXSIZE:
		     s.length();
			 */
		data=s;
		//truncate to max allowed length
		data.resize(MAXSIZE);

	    return *this;
		}
    SMALLCHAR& operator=(const char* s){
		/*
		data.assign(s,
			strlen(s)>MAXSIZE?MAXSIZE:
		    strlen(s);
        size=strlen(s)>MAXSIZE?MAXSIZE:
		     strlen(s);
			 */
		data=s;
		//truncate to max allowed length
		data.resize(MAXSIZE);

		return *this;
		}
	ostream& serialize(ostream& o){
		/*make the string's length
		maximum bcz we r doing fixed 
		length fields
		*/

		data.resize(MAXSIZE);

		o.write((char*)&data.c_str(),data.length()+1);
		/*
		for(int i=size;i<=MAXSIZE;i++){
			o.put(0);
			}*/

		return o;

		}
	istream& deserialize(istream& i){
		char ch;
		for(int j=0;(ch=(char)i.get());j++)
			data+=ch;
		//size=data.length();
		//read in the string until NULL is
		//encountered and then pad the 
		//rest with ZEROS
		//remember its a 4K field


		for(j=data.length();j<=MAXSIZE;j++){
			data+=(char)0;
			}
		return i;
		}

	ostream& <<(ostream& o){
		o<<data;
		return o;
		}
	istream& >>(istream& i){
		i>>data;
		return i;
		}

	SMALLCHAR operator+(SMALLCHAR t){
		SMALLCHAR aux;
		/*
		string aux_str;
		aux_str=data+t.data;
		aux.data.assign(aux_str,0,
			aux_str.length()>MAXSIZE?MAXSIZE:aux_str.length());
		aux.size=aux.data.length();
		*/
		aux.data=data+t;
		//truncate to max allowed length
		aux.data.resize(MAXSIZE);

		return aux;
		}
	SMALLCHAR operator+(const string& s){
		SMALLCHAR aux;
	    /*
		string aux_str;
		aux.data.assign(data+s,0,
			(data+s).length()>MAXSIZE?
			MAXSIZE:(data+s).length());
		aux.size=aux.data.length();
		*/
		aux.data=data+s;
		//truncate to max allowed length
		aux.data.resize(MAXSIZE);

		return aux;

		}
	SMALLCHAR operator+(const char* s){
		SMALLCHAR aux;
		aux.data=data+s;
		aux.data.resize(MAXSIZE);
		return aux;

		}
	SMALLCHAR operator+=(SMALLCHAR t){
		data+=t;
		data.resize(MAXSIZE);
		return *this;

		}
	SMALLCHAR operator+=(const string& s){
		data+=s;
		data.resize(MAXSIZE);
		return *this;
		}
	SMALLCHAR operator+=(const char* s){
		data+=s;
		data.resize(MAXSIZE);
		return *this;

		}
	//return the data as a string

	string value(){
		return data;
		}
	char* value(char* s){
		data.copy(s,data.length());
		return s;
		}
	friend SMALLCHAR operator+(const char* s,
		SMALLCHAR ob);
	friend SMALLCHAR operator+(const string& s,
		SMALLCHAR ob);
	
	friend bool operator<(const SMALLCHAR&,const SMALLCHAR&);
	friend bool operator<(const SMALLCHAR&, const string&);
	friend bool operator<(const string&,const SMALLCHAR&);
	friend bool operator<(const SMALLCHAR&, const char* );
	friend bool operator<(const char*, const SMALLCHAR&);
	
	friend bool operator>(const SMALLCHAR&,const SMALLCHAR&);
	friend bool operator>(const SMALLCHAR&, const string&);
	friend bool operator>(const string&,const SMALLCHAR&);
	friend bool operator>(const SMALLCHAR&, const char* );
	friend bool operator>(const char*, const SMALLCHAR&);

	friend bool operator<=(const SMALLCHAR&,const SMALLCHAR&);
	friend bool operator<=(const SMALLCHAR&, const string&);
	friend bool operator<=(const string&,const SMALLCHAR&);
	friend bool operator<=(const SMALLCHAR&, const char* );
	friend bool operator<=(const char*, const SMALLCHAR&);
	
	friend bool operator>=(const SMALLCHAR&,const SMALLCHAR&);
	friend bool operator>=(const SMALLCHAR&, const string&);
	friend bool operator>=(const string&,const SMALLCHAR&);
	friend bool operator>=(const SMALLCHAR&, const char* );
	friend bool operator>=(const char*, const SMALLCHAR&);

	friend bool operator==(const SMALLCHAR&,const SMALLCHAR&);
	friend bool operator==(const SMALLCHAR&, const string&);
	friend bool operator==(const string&,const SMALLCHAR&);
	friend bool operator==(const SMALLCHAR&, const char* );
	friend bool operator==(const char*, const SMALLCHAR&);

	friend bool operator!=(const SMALLCHAR&,const SMALLCHAR&);
	friend bool operator!=(const SMALLCHAR&, const string&);
	friend bool operator!=(const string&,const SMALLCHAR&);
	friend bool operator!=(const SMALLCHAR&, const char* );
	friend bool operator!=(const char*, const SMALLCHAR&);

	
		};
	SMALLCHAR operator+(const char* s,
		SMALLCHAR ob){
		SMALLCHAR aux;
		aux.data=s+data;
		aux.data.resize(MAXSIZE);
		return aux;
		}
	SMALLCHAR operator+(const string& s,
		SMALLCHAR ob){
		SMALLCHAR aux;
		aux.data=s+data;
		aux.data.resize(MAXSIZE);
		return aux;
		}
	bool operator<(const SMALLCHAR& lhs, const SMALLCHAR& rhs){
		return lhs.data<rhs.data;
		}
	
	bool operator<(const SMALLCHAR& lhs, const string& rhs){
		return lhs.data<rhs;
		}

	bool operator<(const string& lhs,const SMALLCHAR& rhs){

		return lhs<rhs.data;
		}

	bool operator<(const SMALLCHAR& lhs, const char* rhs){
		return lhs.data<rhs;
		}


	friend bool operator<(const char* lhs, const SMALLCHAR& rhs){
		return lhs< rhs.data;
		}

	bool operator>(const SMALLCHAR& lhs, const SMALLCHAR& rhs){
		return lhs.data>rhs.data;
		}
	
	bool operator>(const SMALLCHAR& lhs, const string& rhs){
		return lhs.data>rhs;
		}

	bool operator>(const string& lhs,const SMALLCHAR& rhs){

		return lhs>rhs.data;
		}

	bool operator>(const SMALLCHAR& lhs, const char* rhs){
		return lhs.data>rhs;
		}


	bool operator>(const char* lhs, const SMALLCHAR& rhs){
		return lhs>rhs.data;
		}

	bool operator<=(const SMALLCHAR& lhs, const SMALLCHAR& rhs){
		return lhs.data<=rhs.data;
		}
	
	bool operator<=(const SMALLCHAR& lhs, const string& rhs){
		return lhs.data<=rhs;
		}

	bool operator<=(const string& lhs,const SMALLCHAR& rhs){

		return lhs<=rhs.data;
		}

	bool operator<=(const SMALLCHAR& lhs, const char* rhs){
		return lhs.data<=rhs;
		}


	bool operator<=(const char* lhs, const SMALLCHAR& rhs){
		return lhs<=rhs.data;
		}

	bool operator>=(const SMALLCHAR& lhs, const SMALLCHAR& rhs){
		return lhs.data>=rhs.data;
		}
	
	bool operator>=(const SMALLCHAR& lhs, const string& rhs){
		return lhs.data>=rhs;
		}

	bool operator>=(const string& lhs,const SMALLCHAR& rhs){

		return lhs>=rhs.data;
		}

	bool operator>=(const SMALLCHAR& lhs, const char* rhs){
		return lhs.data>=rhs;
		}


	bool operator>=(const char* lhs, const SMALLCHAR& rhs){
		return lhs>=rhs.data;
		}
	bool operator==(const SMALLCHAR& lhs, const SMALLCHAR& rhs){
		return lhs.data==rhs.data;
		}
	
	bool operator==(const SMALLCHAR& lhs, const string& rhs){
		return lhs.data==rhs;
		}

	bool operator==(const string& lhs,const SMALLCHAR& rhs){

		return lhs==rhs.data;
		}

	bool operator==(const SMALLCHAR& lhs, const char* rhs){
		return lhs.data==rhs;
		}


	bool operator==(const char* lhs, const SMALLCHAR& rhs){
		return lhs==rhs.data;
		}
	
	bool operator!=(const SMALLCHAR& lhs, const SMALLCHAR& rhs){
		return lhs.data!=rhs.data;
		}
	
	bool operator!=(const SMALLCHAR& lhs, const string& rhs){
		return lhs.data!=rhs;
		}

	bool operator!=(const string& lhs,const SMALLCHAR& rhs){

		return lhs!=rhs.data;
		}

	bool operator!=(const SMALLCHAR& lhs, const char* rhs){
		return lhs.data!=rhs;
		}


	bool operator!=(const char* lhs, const SMALLCHAR& rhs){
		return lhs!=rhs.data;
		}



//INTEGER DT

class INTEGER{
private:
	//store the value here
	long data;
public:
    INTEGER ():data(0){}
    INTEGER (long val){
		data=val;
		}
	INTEGER (const INTEGER& ob){
		this->data=ob.data;
		}
	INTEGER operator=(INTEGER ob){
		this->data=ob.data;
		return *this;

		}
	//assign a long to INTEGER

	INTEGER operator=(long ob){
		data=ob;
		return *this;
		}
    // put raw bin data to stream
	
	ostream& serialize(ostream& o){
		o.write((char*)&data, sizeof(data));
		return o;
		}
	//get raw bin data from stream

	istream& deserialize(istream& i){
		i.read((char*)&data,sizeof(data));
		return i;
		}
	//put formatted data to stream in
	// text mode

	ostream& operator<<(ostream& o){
		o<<data;
		return o;
		}
	//get formatted data from stream 
	//in text mode

	istream& operator>>(istream& i){
		i>>data;
		return i;
		}
    long value(){
		return data;
		}
	INTEGER operator+(INTEGER ob){
		INTEGER aux;

		aux.data=data+ob.data;
		return aux;
		}
	INTEGER operator+=(INTEGER ob){
		data+=ob.data;
		return *this;
		}
	 operator long()(){
		 return data;
		 }
	 INTEGER operator+(long l){
		 INTEGER aux;
		 aux.data=data+l;
		 return aux;
		 }
	 INTEGER operator+=(long l){
		 data+=l;
		 return *this;
		 }
	 INTEGER operator-(INTEGER ob){
		 INTEGER aux;
		 aux=data-ob.data;
		 return aux;
		 }
	 INTEGER operator-=(INTEGER ob){
		 data-=ob.data;
		 return *this;
		 }
	 INTEGER operator-(long l){
		 INTEGER aux;
		 aux.data=data-l;
		 return aux;
		 }
	 INTEGER operator-=(long l){
		 data-=l;
		 return *this;
		 }
	 INTEGER operator++(){
		 ++data;
		 return *this;
		 }
	 INTEGER operator++(int){
		 data++;
		 return *this;
		 }
	 INTEGER operator--(){
		 --data;
		 return *this;
		 }
	 INTEGER operator--(int){
		 data--;
		 return *this;
		 }
	 INTEGER operator*(INTEGER ob){
		 INTEGER aux;
		 aux=data*ob.data;
		 return aux;
		 }
	 INTEGER operator*=(INTEGER ob){
		 data*=ob.data;
		 return *this;
		 }
	 INTEGER operator*(long l){
		 INTEGER aux;
		 aux.data=data*l;
		 return aux;
		 }
	 INTEGER operator*=(long l){
		 data*=l;
		 return *this;
		 }

	 INTEGER operator/(INTEGER ob){
		 INTEGER aux;
		 aux.data=data/ob.data;
		 return aux;
		 }
	 INTEGER operator/=(INTEGER ob){
		 data/=ob.data;
		 return *this;
		 }
	 INTEGER operator/(long l){
		 INTEGER aux;
	     aux.data=data/l;
		 return aux;
		 }
	 INTEGER operator/=(long l){
		 data/=l;
		 return *this;
		 }
     INTEGER operator%(INTEGER ob){
		 INTEGER aux;
		 aux.data=data%ob.data;
		 return aux;
		 }
	 INTEGER operator%=(INTEGER ob){
		 data%=ob.data;
		 return *this;
		 }
	 INTEGER operator%(long l){
		 INTEGER aux;
	     aux.data=data%l;
		 return aux;
		 }
	 INTEGER operator%=(long l){
		 data%=l;
		 return *this;
		 }
	 friend INTEGER operator+(long, INTEGER);
	 friend INTEGER operator-(long, INTEGER);
	 friend INTEGER operator/(long, INTEGER);
	 friend INTEGER operator*(long, INTEGER);
	 friend INTEGER operator%(long, INTEGER);

     friend bool operator<(const INTEGER&, const INTEGER&);
	 friend bool operator<(const INTEGER&, const long);
	 friend bool operator<(const long, const INTEGER&);

	 friend bool operator>(const INTEGER&, const INTEGER&);
	 friend bool operator>(const INTEGER&, const long);
	 friend bool operator>(const long, const INTEGER&);

	 friend bool operator<=(const INTEGER&, const INTEGER&);
	 friend bool operator<=(const INTEGER&, const long);
	 friend bool operator<=(const long, const INTEGER&);

	 friend bool operator>=(const INTEGER&, const INTEGER&);
	 friend bool operator>=(const INTEGER&, const long);
	 friend bool operator>=(const long, const INTEGER&);

	 friend bool operator!=(const INTEGER&, const INTEGER&);
	 friend bool operator!=(const INTEGER&, const long);
	 friend bool operator!=(const long, const INTEGER&);

     friend bool operator==(const INTEGER&, const INTEGER&);
	 friend bool operator==(const INTEGER&, const long);
	 friend bool operator==(const long, const INTEGER&);

	};

	 INTEGER operator+(long lhs, INTEGER rhs){
		 INTEGER aux;
		 aux.data=lhs+rhs.data;
		 return aux;
		 }


	 INTEGER operator-(long lhs, INTEGER rhs){
		 INTEGER aux;
		 aux.data=lhs-rhs.data;
		 return aux;
		 }

		 
	 INTEGER operator/(long lhs, INTEGER rhs){
		 INTEGER aux;
		 aux.data=lhs/rhs.data;
		 return aux;
		 }

		 
	 INTEGER operator*(long lhs, INTEGER rhs){
		 INTEGER aux;
		 aux.data=lhs*rhs.data;
		 return aux;
		 
		 }


	 INTEGER operator%(long lhs, INTEGER rhs){
		 INTEGER aux;
		 aux.data=lhs%rhs.data;
		 return aux;
		 }
		 
     bool operator<(const INTEGER& lhs, const INTEGER& rhs){
		 return lhs.data<rhs.data;
		 }


	 bool operator<(const INTEGER& lhs, const long rhs){
		 return lhs.data<rhs;
		 }

	 bool operator<(const long lhs, const INTEGER& rhs){
		 return lhs<rhs.data;
		 }


	 bool operator>(const INTEGER& lhs, const INTEGER& rhs){
		 return lhs.data>rhs.data;
		 }

	 bool operator>(const INTEGER& lhs, const long rhs){
		 return lhs.data>rhs;
		 }

	 bool operator>(const long lhs, const INTEGER& rhs){
		 return lhs>rhs.data;
		 }


	 bool operator<=(const INTEGER& lhs, const INTEGER& rhs){
		 return lhs.data<=rhs.data;
		 }

	 bool operator<=(const INTEGER& lhs, const long rhs){
		 return lhs.data<=rhs;
		 }

	 bool operator<=(const long lhs, const INTEGER& rhs){
		 return lhs<=rhs.data;
		 }


	 bool operator>=(const INTEGER& lhs, const INTEGER& rhs){
		 return lhs.data>=rhs.data;
		 }

	 bool operator>=(const INTEGER& lhs, const long rhs){
		 return lhs.data>=rhs;
		 }

	 bool operator>=(const long lhs, const INTEGER& rhs){
		 return lhs>=rhs.data;
		 }

	 bool operator!=(const INTEGER& lhs, const INTEGER& rhs){
		 return lhs.data!=rhs.data;
		 }

	 bool operator!=(const INTEGER& lhs, const long rhs){
		 return lhs.data!=rhs;
		 }

	 bool operator!=(const long lhs, const INTEGER& rhs){
		 return lhs!=rhs.data;
		 }

	 bool operator==(const INTEGER& lhs, const INTEGER& rhs){
		 return lhs.data>=rhs.data;
		 }

	 bool operator==(const INTEGER& lhs, const long rhs){
		 return lhs.data>=rhs;
		 }

	 bool operator==(const long lhs, const INTEGER& rhs){
		 return lhs>=rhs.data;
		 }

     

class DOUBLE{
private:

	double data;

public:
	DOUBLE():data(0.0){}
	DOUBLE(const DOUBLE& ob){
		data=ob.data;
		}
    DOUBLE(const double d){
		data=d;
		}

	DOUBLE operator=(const DOUBLE& ob){
		data=ob.data;
		return *this;

		}
	DOUBLE operator=(const double d){
		data=d;
		return *this;

		}
		ostream& serialize(ostream& o){
		o.write((char*)&data, sizeof(data));
		return o;
		}
	//get raw bin data from stream

	istream& deserialize(istream& i){
		i.read((char*)&data,sizeof(data));
		return i;
		}
	//put formatted data to stream in
	// text mode

	ostream& operator<<(ostream& o){
		o<<data;
		return o;
		}
	//get formatted data from stream 
	//in text mode

	istream& operator>>(istream& i){
		i>>data;
		return i;
		}
    double value(){
		return data;
		}
	DOUBLE operator+(DOUBLE ob){
		DOUBLE aux;

		aux.data=data+ob.data;
		return aux;
		}
	DOUBLE operator+=(DOUBLE ob){
		data+=ob.data;
		return *this;
		}
	 operator double()(){
		 return data;
		 }
	 DOUBLE operator+(double l){
		 DOUBLE aux;
		 aux.data=data+l;
		 return aux;
		 }
	 DOUBLE operator+=(double l){
		 data+=l;
		 return *this;
		 }
	 DOUBLE operator-(DOUBLE ob){
		 DOUBLE aux;
		 aux=data-ob.data;
		 return aux;
		 }
	 DOUBLE operator-=(DOUBLE ob){
		 data-=ob.data;
		 return *this;
		 }
	 DOUBLE operator-(double l){
		 DOUBLE aux;
		 aux.data=data-l;
		 return aux;
		 }
	 DOUBLE operator-=(double l){
		 data-=l;
		 return *this;
		 }
	 DOUBLE operator++(){
		 ++data;
		 return *this;
		 }
	 DOUBLE operator++(int){
		 data++;
		 return *this;
		 }
	 DOUBLE operator--(){
		 --data;
		 return *this;
		 }
	 DOUBLE operator--(int){
		 data--;
		 return *this;
		 }
	 DOUBLE operator*(DOUBLE ob){
		 DOUBLE aux;
		 aux=data*ob.data;
		 return aux;
		 }
	 DOUBLE operator*=(DOUBLE ob){
		 data*=ob.data;
		 return *this;
		 }
	 DOUBLE operator*(double l){
		 DOUBLE aux;
		 aux.data=data*l;
		 return aux;
		 }
	 DOUBLE operator*=(double l){
		 data*=l;
		 return *this;
		 }

	 DOUBLE operator/(DOUBLE ob){
		 DOUBLE aux;
		 aux.data=data/ob.data;
		 return aux;
		 }
	 DOUBLE operator/=(DOUBLE ob){
		 data/=ob.data;
		 return *this;
		 }
	 DOUBLE operator/(double l){
		 DOUBLE aux;
	     aux.data=data/l;
		 return aux;
		 }
	 DOUBLE operator/=(double l){
		 data/=l;
		 return *this;
		 }
 	 friend DOUBLE operator+(double, DOUBLE);
	 friend DOUBLE operator-(double, DOUBLE);
	 friend DOUBLE operator/(double, DOUBLE);
	 friend DOUBLE operator*(double, DOUBLE);
	 

     friend bool operator<(const DOUBLE&, const DOUBLE&);
	 friend bool operator<(const DOUBLE&, const double);
	 friend bool operator<(const double, const DOUBLE&);

	 friend bool operator>(const DOUBLE&, const DOUBLE&);
	 friend bool operator>(const DOUBLE&, const double);
	 friend bool operator>(const double, const DOUBLE&);

	 friend bool operator<=(const DOUBLE&, const DOUBLE&);
	 friend bool operator<=(const DOUBLE&, const double);
	 friend bool operator<=(const double, const DOUBLE&);

	 friend bool operator>=(const DOUBLE&, const DOUBLE&);
	 friend bool operator>=(const DOUBLE&, const double);
	 friend bool operator>=(const double, const DOUBLE&);

	 friend bool operator!=(const DOUBLE&, const DOUBLE&);
	 friend bool operator!=(const DOUBLE&, const double);
	 friend bool operator!=(const double, const DOUBLE&);

     friend bool operator==(const DOUBLE&, const DOUBLE&);
	 friend bool operator==(const DOUBLE&, const double);
	 friend bool operator==(const double, const DOUBLE&);

	};

	 DOUBLE operator+(double lhs, DOUBLE rhs){
		 DOUBLE aux;
		 aux.data=lhs+rhs.data;
		 return aux;
		 }


	 DOUBLE operator-(double lhs, DOUBLE rhs){
		 DOUBLE aux;
		 aux.data=lhs-rhs.data;
		 return aux;
		 }

		 
	 DOUBLE operator/(double lhs, DOUBLE rhs){
		 DOUBLE aux;
		 aux.data=lhs/rhs.data;
		 return aux;
		 }

		 
	 DOUBLE operator*(double lhs, DOUBLE rhs){
		 DOUBLE aux;
		 aux.data=lhs*rhs.data;
		 return aux;
		 
		 }


	 
		 
     bool operator<(const DOUBLE& lhs, const DOUBLE& rhs){
		 return lhs.data<rhs.data;
		 }


	 bool operator<(const DOUBLE& lhs, const double rhs){
		 return lhs.data<rhs;
		 }

	 bool operator<(const double lhs, const DOUBLE& rhs){
		 return lhs<rhs.data;
		 }


	 bool operator>(const DOUBLE& lhs, const DOUBLE& rhs){
		 return lhs.data>rhs.data;
		 }

	 bool operator>(const DOUBLE& lhs, const double rhs){
		 return lhs.data>rhs;
		 }

	 bool operator>(const double lhs, const DOUBLE& rhs){
		 return lhs>rhs.data;
		 }


	 bool operator<=(const DOUBLE& lhs, const DOUBLE& rhs){
		 return lhs.data<=rhs.data;
		 }

	 bool operator<=(const DOUBLE& lhs, const double rhs){
		 return lhs.data<=rhs;
		 }

	 bool operator<=(const double lhs, const DOUBLE& rhs){
		 return lhs<=rhs.data;
		 }


	 bool operator>=(const DOUBLE& lhs, const DOUBLE& rhs){
		 return lhs.data>=rhs.data;
		 }

	 bool operator>=(const DOUBLE& lhs, const double rhs){
		 return lhs.data>=rhs;
		 }

	 bool operator>=(const double lhs, const DOUBLE& rhs){
		 return lhs>=rhs.data;
		 }

	 bool operator!=(const DOUBLE& lhs, const DOUBLE& rhs){
		 return lhs.data!=rhs.data;
		 }

	 bool operator!=(const DOUBLE& lhs, const double rhs){
		 return lhs.data!=rhs;
		 }

	 bool operator!=(const double lhs, const DOUBLE& rhs){
		 return lhs!=rhs.data;
		 }

	 bool operator==(const DOUBLE& lhs, const DOUBLE& rhs){
		 return lhs.data>=rhs.data;
		 }

	 bool operator==(const DOUBLE& lhs, const double rhs){
		 return lhs.data>=rhs;
		 }

	 bool operator==(const double lhs, const DOUBLE& rhs){
		 return lhs>=rhs.data;
		 }



class TEXT {
private:
	string data;
	//int size;
	const int MAXSIZE=4*1024;


public:
	TEXT()/*:size(0)*/{}
	TEXT(const string& s){
		/*
		data.assign(s,0,
			s.length()>MAXSIZE?MAXSIZE
			:s.length());
		size=s.length()>MAXSIZE?MAXSIZE:
		     s.length();
			 */
		data=s;
		data.resize(MAXSIZE);

		}
	TEXT (const char* s){
		/*
		data.assign(s, strlen(s)()>MAXSIZE?
        MAXSIZE:strlen(s));
		size=strlen(s)>MAXSIZE?MAXSIZE:
		     strlen(s);
			 */
		data=s;
		data.resize(MAXSIZE);

		}
	TEXT& operator=(const TEXT& t){
		data=t;
		size=t.length();
		return *this;

		}
	TEXT& operator=(const string& s){
		/*
		data.assign(s,0,
			s.length()>MAXSIZE?
            MAXSIZE:s.length());
		size=s.length()>MAXSIZE?MAXSIZE:
		     s.length();
			 */
		data=s;
		data.resize(MAXSIZE);

	    return *this;
		}
    TEXT& operator=(const char* s){
		/*
		data.assign(s,
			strlen(s)>MAXSIZE?MAXSIZE:
		    strlen(s);
        size=strlen(s)>MAXSIZE?MAXSIZE:
		     strlen(s);
			 */
		data=s;
		data.resize(MAXSIZE);

		return *this;
		}
	ostream& serialize(ostream& o){
		data.resize(MAXSIZE);

		o.write((char*)&data.c_str(),data.length()+1);
		/*
		for(int i=size;i<=MAXSIZE;i++){
			o.put(0);
			}*/

		return o;

		}
	istream& deserialize(istream& i){
		char ch;
		for(int j=0;(ch=(char)i.get());j++)
			data+=ch;
		size=data.length();

		for(j=data.length();j<=MAXSIZE;j++){
			data+=(char)0;
			}
		return i;
		}

	ostream& <<(ostream& o){
		o<<data;
		return o;
		}
	istream& >>(istream& i){
		i>>data;
		return i;
		}

	TEXT operator+(TEXT t){
		TEXT aux;
		/*
		string aux_str;
		aux_str=data+t.data;
		aux.data.assign(aux_str,0,
			aux_str.length()>MAXSIZE?MAXSIZE:aux_str.length());
		aux.size=aux.data.length();
		*/
		aux.data=data+t;
		aux.data.resize(MAXSIZE);

		return aux;
		}
	TEXT operator+(const string& s){
		TEXT aux;
		/*
		string aux_str;
		aux.data.assign(data+s,0,
			(data+s).length()>MAXSIZE?
			MAXSIZE:(data+s).length());
		aux.size=aux.data.length();
		*/
		aux.data=data+s;
		aux.data.resize(MAXSIZE);

		return aux;

		}
	TEXT operator+(const char* s){
		TEXT aux;
		aux.data=data+s;
		aux.data.resize(MAXSIZE);
		return aux;


		}
	TEXT operator+=(TEXT t){
		data+=t;
		data.resize(MAXSIZE);
		return *this;

		}
	TEXT operator+=(const string& s){
		data+=s;
		data.resize(MAXSIZE);
		return *this;
		}
	TEXT operator+=(const char* s){
		data+=s;
		data.resize(MAXSIZE);
		return *this;

		}
	string value(){
		return data;
		}
	friend TEXT operator+(const char* s,
		TEXT ob);
	friend TEXT operator+(const string& s,
		TEXT ob);
	
	friend bool operator<(const TEXT&,const TEXT&);
	friend bool operator<(const TEXT&, const string&);
	friend bool operator<(const string&,const TEXT&);
	friend bool operator<(const TEXT&, const char* );
	friend bool operator<(const char*, const TEXT&);
	
	friend bool operator>(const TEXT&,const TEXT&);
	friend bool operator>(const TEXT&, const string&);
	friend bool operator>(const string&,const TEXT&);
	friend bool operator>(const TEXT&, const char* );
	friend bool operator>(const char*, const TEXT&);

	friend bool operator<=(const TEXT&,const TEXT&);
	friend bool operator<=(const TEXT&, const string&);
	friend bool operator<=(const string&,const TEXT&);
	friend bool operator<=(const TEXT&, const char* );
	friend bool operator<=(const char*, const TEXT&);
	
	friend bool operator>=(const TEXT&,const TEXT&);
	friend bool operator>=(const TEXT&, const string&);
	friend bool operator>=(const string&,const TEXT&);
	friend bool operator>=(const TEXT&, const char* );
	friend bool operator>=(const char*, const TEXT&);

	friend bool operator==(const TEXT&,const TEXT&);
	friend bool operator==(const TEXT&, const string&);
	friend bool operator==(const string&,const TEXT&);
	friend bool operator==(const TEXT&, const char* );
	friend bool operator==(const char*, const TEXT&);

	friend bool operator!=(const TEXT&,const TEXT&);
	friend bool operator!=(const TEXT&, const string&);
	friend bool operator!=(const string&,const TEXT&);
	friend bool operator!=(const TEXT&, const char* );
	friend bool operator!=(const char*, const TEXT&);

	
		};
	TEXT operator+(const char* s,
		TEXT ob){
		TEXT aux;
		aux.data=s+data;
		aux.data.resize(MAXSIZE);
		return aux;
		}
	TEXT operator+(const string& s,
		TEXT ob){
		TEXT aux;
		aux.data=s+data;
		aux.data.resize(MAXSIZE);
		return aux;
		}
	bool operator<(const TEXT& lhs, const TEXT& rhs){
		return lhs.data<rhs.data;
		}
	
	bool operator<(const TEXT& lhs, const string& rhs){
		return lhs.data<rhs;
		}

	bool operator<(const string& lhs,const TEXT& rhs){

		return lhs<rhs.data;
		}

	bool operator<(const TEXT& lhs, const char* rhs){
		return lhs.data<rhs;
		}


	friend bool operator<(const char* lhs, const TEXT& rhs){
		return lhs< rhs.data;
		}

	bool operator>(const TEXT& lhs, const TEXT& rhs){
		return lhs.data>rhs.data;
		}
	
	bool operator>(const TEXT& lhs, const string& rhs){
		return lhs.data>rhs;
		}

	bool operator>(const string& lhs,const TEXT& rhs){

		return lhs>rhs.data;
		}

	bool operator>(const TEXT& lhs, const char* rhs){
		return lhs.data>rhs;
		}


	bool operator>(const char* lhs, const TEXT& rhs){
		return lhs>rhs.data;
		}

	bool operator<=(const TEXT& lhs, const TEXT& rhs){
		return lhs.data<=rhs.data;
		}
	
	bool operator<=(const TEXT& lhs, const string& rhs){
		return lhs.data<=rhs;
		}

	bool operator<=(const string& lhs,const TEXT& rhs){

		return lhs<=rhs.data;
		}

	bool operator<=(const TEXT& lhs, const char* rhs){
		return lhs.data<=rhs;
		}


	bool operator<=(const char* lhs, const TEXT& rhs){
		return lhs<=rhs.data;
		}

	bool operator>=(const TEXT& lhs, const TEXT& rhs){
		return lhs.data>=rhs.data;
		}
	
	bool operator>=(const TEXT& lhs, const string& rhs){
		return lhs.data>=rhs;
		}

	bool operator>=(const string& lhs,const TEXT& rhs){

		return lhs>=rhs.data;
		}

	bool operator>=(const TEXT& lhs, const char* rhs){
		return lhs.data>=rhs;
		}


	bool operator>=(const char* lhs, const TEXT& rhs){
		return lhs>=rhs.data;
		}
	bool operator==(const TEXT& lhs, const TEXT& rhs){
		return lhs.data==rhs.data;
		}
	
	bool operator==(const TEXT& lhs, const string& rhs){
		return lhs.data==rhs;
		}

	bool operator==(const string& lhs,const TEXT& rhs){

		return lhs==rhs.data;
		}

	bool operator==(const TEXT& lhs, const char* rhs){
		return lhs.data==rhs;
		}


	bool operator==(const char* lhs, const TEXT& rhs){
		return lhs==rhs.data;
		}
	
	bool operator!=(const TEXT& lhs, const TEXT& rhs){
		return lhs.data!=rhs.data;
		}
	
	bool operator!=(const TEXT& lhs, const string& rhs){
		return lhs.data!=rhs;
		}

	bool operator!=(const string& lhs,const TEXT& rhs){

		return lhs!=rhs.data;
		}

	bool operator!=(const TEXT& lhs, const char* rhs){
		return lhs.data!=rhs;
		}


	bool operator!=(const char* lhs, const TEXT& rhs){
		return lhs!=rhs.data;
		}























	  