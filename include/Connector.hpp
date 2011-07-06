// developer: faisal
//
// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL

#ifndef __SQL_CONNECTORHPP
#define __SQL_CONNECTORHPP

#include <Base.hpp>
#include <SQLList.hpp>
#include <Database.h>
#include <Table.h>
#include <Field.hpp>
#include <SQL.hpp>

class Client;

class globalCMP : public SMADCMP { bool cmp ( RECORD& rec ); };
class searchCMP : public SMADCMP { bool cmp ( RECORD& rec ); };

namespace SMADdbConnector
{
	extern Client* C;

	int ParserToFiler ( int type );
	int FilerToParser ( int type );

	// Return Values: True/False whether the operation was successful
	int CreateTable ( DataBase* db , char* tablename , SQLList<SQLnewfield*>* lst );
	int DeleteTable ( DataBase* db , char* tablename );

	// Return values: NUMBER OF RECORDS AFFECTED
	int SelectRecord ( Table* table , SQLList <TreeExpr*>* lst , SQLList<Column*>* fields , SQLList<SQLsearch*>* search , char* out );
	int InsertRecord ( Table* , SQLList<SQLassign*>* );
	int UpdateRecord ( Table* , SQLList<SQLassign*>* , SQLList<SQLsearch*>* );
	int DeleteRecord ( Table* , SQLList<SQLsearch*>* );

	bool VerifyTable (Table* t);
	SMAD_RECORD* ConvertRecord (RECORD& rec);
}

#endif
