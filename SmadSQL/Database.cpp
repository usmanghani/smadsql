// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
//
// Provides various database functions

#include <Base.hpp>
#include <Database.hpp>
#include <Table.hpp>

std::map<std::string,std::string> DBLIST::dblist;
bool DBLIST::isInit;
std::string DBLIST::DBlistfile;

bool DBLIST::DBExists(const DataBase& d)
{
	return true;
	//	return dblist[d.GetName()].length();
}

int DBLIST::CreateNewDataBase(const std::string& name)
{
	if(dblist.find(name)!= dblist.end())
		return DATABASE_ALREADY_EXISTS;

	std::string aux = name+std::string(".SMAD");

	ofstream out(DBlistfile.c_str(),ios::binary|ios::app);
	out.write(name.c_str(),name.length()+1);
	out.write(aux.c_str(),aux.length()+1);

//	dblist[name] = aux;
	out.close();
	return 0;
}

int DBLIST::InitList (char* name)
{
	char listfile [512];
	strcpy ( listfile , DBPATH );
	strcat ( listfile , name );
	strcat ( listfile , ".db" );

	cout << "===READING LIST " << listfile << "===" << endl;
	ifstream dblstfile ( listfile ,ios::binary|ios::in);
	if ( !dblstfile ) return DB_LIST_FILE_CANT_BE_OPENED;

	while ( ! dblstfile.eof() )
	{
		std::string dbname;
		std::string dbpath;
		char ch = 0;

		while ( (ch=dblstfile.get())!=',' && !dblstfile.eof() )
			dbname+=ch;

		while ( (ch=dblstfile.get())!='\n' && !dblstfile.eof() )
			dbpath+=ch;

		if ( dbname.length () )
			dblist[dbname] = dbpath;
	}
	dblstfile.close();

	isInit = true;
	return SMAD_NO_ERROR;
}

SQLList<Table*>* DataBase::GetTables()
{
	SQLList<Table*>* l = new SQLList<Table*>;
	for( std::map<std::string,Table*>::const_iterator it=TABLES.begin();
		it!=TABLES.end() ; it++)
		l->push(it->second);
	return l;
}

int DataBase::OpenDB (char* name)
{
	char* dbpath = (char*) DBLIST::dblist[std::string(name)].c_str();
	cout << "OPENING DATABASE: " << dbpath << endl;

	ifstream stream ( dbpath , ios::binary | ios::in );
	if ( ! stream.good() ) return DB_FILE_CANT_BE_OPENED;

	while(!stream.eof())
	{
		std::string tname , tpath;
		char ch;
		while ( (ch=stream.get())!=',' && !stream.eof() )	tname+=ch;
		while ( (ch=stream.get())!='\n' && !stream.eof() )	tpath+=ch;

		if ( tname.length () )
		{
			Table* t = new Table ( strdup ( tname.c_str() ) , strdup ( tpath.c_str() ) );
			TABLES [tname] = t;
		}
	}
	stream.close();
	return 0;
}


Table* DataBase::OpenTable (char* name)
{
	std::string s = std::string (name);

	if ( TABLES.find(s) == TABLES.end() )
		return new Table(name); //return TABLE_DOES_NOT_EXIST;

	Table* t = TABLES [name];
	if ( t->ISOPEN == true ) return t;

	char* path = t->GetPath ();
	std::string p = path + std::string(".tbl");
	enum fld_typ fieldtype;
	FIELD_DEF aux_fld;

	cout << "ATTEMPTING TO READ TABLE: " << name << endl;
	ifstream stream ( p.c_str() , ios::binary|ios::in);

	stream.read((char*)&t->num_recs,sizeof(t->num_recs));
	stream.read((char*)&t->rec_size,sizeof(t->rec_size));

	while(!stream.eof())
	{
		std::string fieldname;
		char ch;
		while ( (ch=stream.get())!=',' && !stream.eof() )	fieldname+=ch;
		stream.read((char*)&fieldtype,sizeof(enum fld_typ));
		aux_fld.name = fieldname;
		aux_fld.type = fieldtype;
//		t->PutField(aux_fld);
	}
		
	std::string tblfilename,idxfilename;
	tblfilename = path + std::string(".dat");
	idxfilename = path + std::string(".idx");

	t->StreamData.open ( tblfilename.c_str() , ios::in|ios::app|ios::binary );
	t->StreamIndex.open( idxfilename.c_str() , ios::binary|ios::in|ios::app );
	t->ISOPEN = 1;

	return t;
}
