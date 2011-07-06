#include "glblinc.h"
#include "data_objects.h"


	SMADVARIANT& RECORD::GetValue( const string& fld_name)  {
		return mv[fld_name];
	}
	SMADVARIANT& RECORD::GetValue(unsigned long l){
		map<string,SMADVARIANT>::iterator iter=mv.begin();
		for(;l;--l) iter++;
		return iter->second;
	}

    SMADVARIANT& RECORD::PutValue(unsigned long l,  SMADVARIANT& v){
		map<string,SMADVARIANT>::iterator iter=mv.begin();
		for(;l;--l) iter++;
		iter->second=v;
		return iter->second;
	}

	SMADVARIANT& RECORD::PutValue(const string& fld_name,
		 SMADVARIANT& v){
		mv[fld_name]=v;
		return mv[fld_name];

		
	}
	unsigned long RECORD::GetFieldCount() const{
		return mv.size();
	}
	const map<string,SMADVARIANT>& RECORD::GetFields()const {
		return mv;
	}

	char* RECORD::GetRecordString() const
	{
		char* str = new char [1024*8];
		strcpy ( str , "" );
//		map<string,SMADVARIANT>::const_iterator iter = mv.begin();
//		while(iter!=mv.end()){
//			strcat ( str , (char*) iter->second );
//			strcat ( str , "," );
//			iter++;
//		}
		return str;
	}

	ostream& operator<<(ostream& ostr, const RECORD& rec){
		map<string,SMADVARIANT>::const_iterator iter = rec.mv.begin();
		while(iter!=rec.mv.end()){
			ostr<<iter->second;
			ostr<<'\t';
			iter++;
		}
		return ostr;
	}
	

	std::ostrstream& operator<<(std::ostrstream& ostr, const RECORD& rec){
		map<string,SMADVARIANT>::const_iterator iter = rec.mv.begin();
		while(iter!=rec.mv.end()){
			ostr<<iter->second;
			ostr<<'\t';
			iter++;
		}
		return ostr;
	}
	

     
		