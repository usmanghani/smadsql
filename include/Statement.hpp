// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal

#ifndef __SQL_STATEMENTHPP
#define __SQL_STATEMENTHPP

class Statement
{
public:
	enum TYPE { SQLSELECT , SQLINSERT , SQLUPDATE , SQLDELETE , SQLCREATE };

	char* output;
	SQLList<Column*>	* fieldlist;	// set of fields used in the query (anywhere!)
	SQLList<TreeExpr*>	* fields;		// set of expressions to return to the client
	SQLList<Table*>		* tables;		// set of tables that have been used in query
	SQLList<SQLsearch*>	* search;		// search construct

	// Result RecordSet
//	RECORDSET* RS;
	void* RS;

	Statement	()		{ fields = 0; tables = 0; search = 0; RS = 0; }
	~Statement	()		{
		delete search;
		//delete fields;
		//delete tables;
		//delete fieldlist;
		//delete RS;
	} //delete search
};

#endif