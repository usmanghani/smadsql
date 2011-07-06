#ifndef __RECORD_H
#define __RECORD_H

#include <strstream>
#include <string>

class RECORD;

std::ostream& operator<<(std::ostream&,const RECORD&);
std::ostrstream& operator<<(std::ostrstream&,const RECORD&);

class RECORD{
	map<string,SMADVARIANT> mv;

public:
	/*
	~RECORD(){
		map<string, SMADVARIANT>::iterator iter=mv.begin();
		for(;iter!=mv.end();iter++) delete iter->second;
	}
     */
	SMADVARIANT& GetValue( const string& fld_name);
	SMADVARIANT& GetValue(unsigned long l);
    SMADVARIANT& PutValue(unsigned long l,  SMADVARIANT& v);
	SMADVARIANT& PutValue(const string& fld_name, SMADVARIANT& v);
	char* GetRecordString() const;
	unsigned long GetFieldCount() const;
	const map<string,SMADVARIANT>& GetFields()const;
	friend std::ostream& operator<<(std::ostream&,const RECORD&);
	friend std::ostrstream& operator<<(std::ostrstream&,const RECORD&);

	friend class Table;
};

#endif
