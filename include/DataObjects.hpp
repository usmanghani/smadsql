//	these r the constants for data types 
// the codes signify which data type is being used
// used in the record and field specification

#define TYPE_INTEGER	0
#define TYPE_DOUBLE		1
#define TYPE_SMALLCHAR	2
#define TYPE_TEXT		3


enum fld_typ{
	typSMALLCHAR,
	typDOUBLE,
	typTEXT,
	typINTEGER,
	typAUTONUMBER
};


class TABLE
{
	char* name;
	char* filename;
	//the list of fields

	vector<FIELD_DEF> field_defs;

public:
	TABLE();
	TABLE(const char* name);

	bool		open(char* name);
	RECORD&		GetRecord (RECORD& );
	bool		InsertRecord (const RECORD& );
	bool		update_record (const RECORD& );
};



template<class T>
class FIELD{
	T data;
	char* name;

public:
	char*	GetName();
	T		GetData() const;
};


class RECORD
{
public:
	vector <VARIANT> data;
};



class RECORDSET
{
    vector <FIELD_DEF> field_defs;
	vector<RECORD> records;
public:
	bool insert_record(RECORD& );
	RECORD& get_record(RECORD& );
	bool insert_record(RECORD& );
	bool write_to_table(string tablename);
	bool refresh()
};