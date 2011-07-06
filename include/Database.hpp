// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: usman

#define SMAD_NO_ERROR 0
#define DB_LIST_FILE_CANT_BE_OPENED 1
#define DB_FILE_CANT_BE_OPENED 2
#define TABLE_DOES_NOT_EXIST 3
#define TABLE_ALREADY_EXISTS 4
#define DATABASE_ALREADY_EXISTS 5

#ifndef __SQL_DATABASEHPP
#define __SQL_DATABASEHPP

#define DBPATH		"c:\\tmp\\smadsql\\"

#include <Table.hpp>

class DataBase;

namespace DBLIST
{
	extern std::map<std::string,std::string> dblist;
	extern bool isInit;
	extern std::string DBlistfile;

	bool DBExists			(const DataBase& d);
	int CreateNewDataBase	(const std::string& name);
	int InitList			(char*name);
};

class DataBase
{
	char* name;
	char* path;
	std::map<std::string,Table*> TABLES;

public:
	DataBase ()				{};
	DataBase (char* name)	{ OpenDB (name); };

	char*	GetName		()				{ return name; }
	Table*	GetTable	(char* name)	{ return OpenTable (name); }
	void	CloseTable	(char*);

	SQLList<Table*>*	GetTables	();
	Table*				OpenTable	(char*);
	int					OpenDB		(char*);

	~DataBase ()
	{
		// each table handles its own cleanup
		for( std::map<std::string,Table*>::const_iterator it = TABLES.begin();
			it != TABLES.end(); it++)
				delete it->second;
	}

	//this method is for creating a new table and adding it to the data base;
//	Table*	CreateTable ( char* name , std::vector<SMADVARIANT> );
};

#endif
