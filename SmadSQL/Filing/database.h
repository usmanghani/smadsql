#ifndef __DATABASE_H
#define __DATABASE_H

#include "Table.h"
#include <vector>

using std::vector;

class DataBase {
	string name;
	string filename;
	//this file is used to store the data abt the tables of th database
//	fstream dbfile;
	smadfiler dbfile;

//this is the vector of tables 
//it is private, the list of tables can be obtained
// by using the method get_tables();
    
	map<string,Table*> tables;
	map<string,Table*> open_tables;
	// making the empty constructor private 
	// to prohibit the creation of a nameless
	// DB



public:
	DataBase(){}
	DataBase(const string& );
	DataBase(const char* );
	~DataBase();
	int open(const string&);
	const string& GetName() const;
//returns a reference to the internal list of tables
	const map<string,Table*>& get_tables() const;
	const map<string,Table*>& get_open_tables() const;
	bool is_table_open(const string& ) const;
	Table* open_table(const string& );
	Table* open_table(const char* );
   //this method is for adding a table from some other database
	bool add_table(DataBase&, Table&);
	//this method is for creating a new table and adding it to the data base;
	int create_table(const string& , const vector<FIELD_DEF>&);
    bool table_exists(const string& ) const;	
	Table*	GetTable	(char* name);
};
#endif
