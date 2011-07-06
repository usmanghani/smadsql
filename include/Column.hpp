#ifndef __SQL_COLUMNHPP
#define __SQL_COLUMNHPP

#include <Base.hpp>
#include <Database.h>
#include <Table.h>
#include <Field.hpp>

// this is the column reference holder
// not the data container
class Column
{
public:
	char*		name;
	DataBase*	db;
	Table*		table;

	Column (DataBase* db , Table* t) { this->db = db; this->table = t; }
	Column (DataBase* db , Table* t , char* name ) { this->db = db; this->table = t; this->name = name; }
};

#endif
