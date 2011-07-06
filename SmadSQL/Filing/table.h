#ifndef __TABLE_H
#define __TABLE_H

#define MAX_DEL_RECS		1024

#include <map>
#include <string>

using std::map;
using std::string;

#include "smadfiler.h"
#include "enumdef.h"

struct FIELD_DEF;
class SMADFiler;
class RECORD;
class RECORDSET;

class SMADCMP
{
public:
	void* ptr; // to store arguments of any sort, example search parameters
	virtual bool cmp (RECORD &rec) { cerr << "ERROR! NO HANDLER!"; return 0; }
};
typedef SMADCMP* CMPFN;
RECORD* GetUpdateValues(RECORD*);

//typedef bool (*CMPFN)(const RECORD&,void* ptr);
class Table
{
	// name of the table
	string name;
	// table data file
	string filename;
	//table index filename wont be needed in the 
	// present scenario
	string idxfilename;
	// table definition filename 
    string deffilename;
	//  the number of records 
	unsigned long num_recs;
	// the size of each record 
	unsigned long rec_size;
	// the number of deleted records in the 
	// deleted_recs  array
	unsigned long num_del_recs;
	// the pointers to the deleted records
	long deleted_recs[MAX_DEL_RECS];
    smadfiler tblfile,idxfile,deffile;
    
	//the list of fields
	map<string,FIELD_DEF> field_defs;
	bool is_record_deleted(long ptr_to_rec);

public:
//	Table();
//	Table(const string& name);
//	Table(const char* name);
    ~Table();
//	open(string name);
//	open(char* name);
	int open();
	
	//these five functions form the real essence of the whole 
	//storage system
    ////////////////////////////////////////////////////////
	int get_record(RECORD& , CMPFN);
	int insert_record(RECORD& );
	int update_record(CMPFN );
	int delete_record(CMPFN );
	int get_recordset(RECORDSET& , CMPFN);
    ////////////////////////////////////////////////////////

	void SetName(const string& );
	string GetName() const;
	void SetIndexFileName(const string&);
	string GetIndexFileName()const;
	void SetDefFileName(const string&);
	string GetDefFileName()const;
	void SetTableFileName(const string& );
	string GetTableFileName() const;
    void PutField(const FIELD_DEF& );
	FIELD_DEF GetField(const string& name) ;
    const map<string,FIELD_DEF>& GetFields() const;
    int write_record(RECORD&);
	int read_record(RECORD&);
	
    friend class DataBase;
};
#endif
