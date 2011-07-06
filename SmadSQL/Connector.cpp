// developer: faisal
//
// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
//
// Connects the parser to the filing model
// by providing gateway routines

#include <Base.hpp>
#include <Client.hpp>
#include <Database.h>
#include <Table.h>
#include <Connector.hpp>
#include <SQL.hpp>
#include <strstrea.h>

#include "smadfiler.h"
#include "integer.h"
#include "double.h"
#include "variant.h"
#include "smallchar.h"
#include "text.h"
#include "data_objects.h"

class SMADSMALLCHAR;
class SMADVARIANT;
class SMADTEXT;
class SMADDOUBLE;
class SMADINTEGER;

#include <Client.hpp>

Client* SMADdbConnector::C;

bool globalCMP::cmp ( RECORD& rec ) { return true; }
bool searchCMP::cmp ( RECORD& rec )
{
	SMAD_RECORD* s = SMADdbConnector::ConvertRecord ( rec );
	int res = ParseSearchExpression ( (SQLList<SQLsearch*>*) ptr , s ); 
	delete s;
	return res > 0 ? 1 : 0;
}

SMAD_RECORD* SMADdbConnector::ConvertRecord (RECORD& rec)
{
	map<string,SMADVARIANT> oldrec = rec.GetFields();
	map<string,SMADVARIANT>::iterator iter = oldrec.begin();
	SMAD_RECORD* newrec = new SMAD_RECORD;

//	std::cerr << rec << "===";

	while(iter!=oldrec.end())
	{
		SQLvariant* S = new SQLvariant;
		char* name = strdup ( (iter->first).c_str() );
		int type = FilerToParser ( iter->second.get_type () );

		switch ( type )
		{
			case TYPE_INTEGER:
			case TYPE_DOUBLE:
				S->type = 0;
				S->val = new double ( (double) iter->second );
				break;
			case TYPE_SMALLCHAR:
			case TYPE_TEXT:
				string s = (string) iter->second;
				S->type = 1;
				S->str = strdup ( s.c_str() );
				break;
		}

//		std::cout << "OUTPUT: " << s << "=" << S->toSTRING () << "\n";
		(*newrec) [name] = S;
		iter++;
	}
	return newrec;
}

int SMADdbConnector::ParserToFiler ( int type )
{
	switch ( type )
	{
		case TYPE_INTEGER:
			return typINTEGER;
			break;
		case TYPE_DOUBLE:
			return typDOUBLE;
			break;
		case TYPE_SMALLCHAR:
			return typSMALLCHAR;
			break;
		case TYPE_TEXT:
			return typTEXT;
			break;
		default:
			return typINTEGER;
			break;
	}
}

int SMADdbConnector::FilerToParser ( int type )
{
	switch ( type )
	{
		case typINTEGER:
			return TYPE_INTEGER;
			break;
		case typDOUBLE:
			return TYPE_DOUBLE;
			break;
		case typSMALLCHAR:
			return TYPE_SMALLCHAR;
			break;
		case typTEXT:
			return TYPE_TEXT;
			break;
		default:
			return TYPE_INTEGER;
			break;
	}
}

bool SMADdbConnector::VerifyTable (Table* t)
{
	if ( t == NULL )
	{
		std::cerr << "SERVER> INVALID TABLE" << "\n";
		return false;
	}
	return true;
}

int SMADdbConnector::CreateTable ( DataBase* db , char* tablename , SQLList<SQLnewfield*>* lst )
{
	vector<FIELD_DEF> fields;
	FIELD_DEF aux_fld;

	for ( unsigned int i=0 ; i<lst->Count() ; i++)
	{
		SQLnewfield* f = lst->at(i);
		aux_fld.name = f->name;
		aux_fld.type = static_cast <fld_typ> ( ParserToFiler ( f->type ) );
//		std::cerr << "NEW FIELD: " << aux_fld.name << " (" << aux_fld.type << ")" << endl;
		fields.push_back(aux_fld);
	}
	return db->create_table ( tablename , fields );
}

int SMADdbConnector::DeleteTable ( DataBase* db , char* tablename )
{
	return true;
}

int SMADdbConnector::InsertRecord ( Table* table , SQLList<SQLassign*>* lst )
{
	if ( ! VerifyTable ( table ) ) return -1;

	RECORD r;
	RECORDSET rset;
	for ( unsigned int i = 0 ; i < lst -> Count () ; i++ )
	{
		char* name = lst->at(i)->field->name;
		FIELD_DEF f = table->GetField ( name );
		if ( strcmp ( name , f.name.c_str() ) )
		{
			std::cerr << "SERVER> Field '" << name << "' does not exist in the table '" << table->GetName() << "'";
			return -1;
		}
		SQLvariant* v = ParseTree ( lst->at(i)->expr , 0 );

		std::cout << "LEFT: " << name << " TYPE: " << FilerToParser (f.type) << " VAL: " << v->toSTRING() << "\n";
	
		switch ( FilerToParser (f.type) )
		{
		case TYPE_INTEGER:
			r.PutValue ( name , SMADVARIANT(new SMADINTEGER( static_cast <long> (v->toVALUE()) )));
			break;
		case TYPE_DOUBLE:
			r.PutValue ( name , SMADVARIANT(new SMADDOUBLE(v->toVALUE())));
			break;
		case TYPE_TEXT:
			r.PutValue ( name , SMADVARIANT(new SMADTEXT(v->toSTRING())));
			break;
		case TYPE_SMALLCHAR:
			r.PutValue ( name , SMADVARIANT(new SMADSMALLCHAR(v->toSTRING())));
			break;
		default:
			r.PutValue ( name , SMADVARIANT(new SMADINTEGER( static_cast <long> (v->toVALUE()) )));
			break;
		}
	}
	int ret = table->insert_record(r);
	
	table->get_recordset(rset,new globalCMP ());

	for(unsigned long ul=0;ul<rset.GetRecordCount();ul++){
		std::cout << rset.FetchRecord() << "\n";
	}
	std::cout<<"Number of Record(s) Fetched: "<<ul<<endl;
		
	return ret;

	/*
	rset.DumpRecordSet(std::cout);
	std::cout<<"Number of Record(s) Dumped: "<<
		rset.GetRecordCount()<<endl;
	std::cin.get();

	for(unsigned long ul=0;ul<rset.GetRecordCount();ul++)
		std::cout<<rset.GetRecord(ul)<<endl;

	std::cout<<"Number of Record(s) Displayed: "<<ul<<endl;
	std::cin.get();
*/
}

int SMADdbConnector::UpdateRecord ( Table* table , SQLList<SQLassign*>* lst , SQLList<SQLsearch*>* search )
{
	if ( ! VerifyTable ( table ) ) return -1;
	return 0;
}

int SMADdbConnector::DeleteRecord ( Table* table , SQLList<SQLsearch*>* search )
{
	if ( ! VerifyTable ( table ) ) return -1;

	SMADCMP* cmp = (SMADCMP*) new searchCMP ();
	cmp->ptr = search;

	table->delete_record(cmp);
	return 0;
}

//ffffffffffff

int SMADdbConnector::SelectRecord ( Table* table , SQLList <TreeExpr*>* lst , SQLList<Column*>* fields , SQLList<SQLsearch*>* search , char* out )
{
	if ( ! VerifyTable ( table ) ) return -1;
	RECORDSET rset;
	//SMADCMP* cmp = (SMADCMP*) new searchCMPclass ();
	SMADCMP* cmp = (SMADCMP*) new searchCMP ();

	cmp->ptr = search;
	table->get_recordset(rset,cmp);
//	ostrstream o;
//	rset.DumpRecordSet( (std::ostream&) o);

	for(unsigned long ul=0;ul<rset.GetRecordCount();ul++)
	{
		RECORD&r = rset.FetchRecord();
		SMAD_RECORD* s = SMADdbConnector::ConvertRecord ( r );

		for (unsigned int i=0;i<lst->Count();i++)
		{
			SQLvariant* v = ParseTree ( lst->at(i) , s ); 
			std::cout << v->toSTRING() << " , ";
		}
		delete s;
		std::cout << "\n";

		//std::ostrstream o;
		//o << rset.FetchRecord();
		//o << ends;
		//strcat ( out , o.str () );
	}

	for(unsigned long ul=0;ul<rset.GetRecordCount();ul++)
	{
		RECORD&r = rset.FetchRecord();
		//SMAD_RECORD::iterator i = s->begin ();
//		SMAD_RECORD* s = ConvertRecord ( r );
//		std::cout << "RECORD [age] = " << (*s) ["age"]->toSTRING() << "\n";
	}


//	for(unsigned long ul=0;ul<rset.GetRecordCount();ul++){
//		std::cout << rset.FetchRecord().GetRecordString () << "\n";

		//	}
//	o << ends;
//	//std::cout << o.str ();
//	std::cout<<"Number of Record(s) Fetched: "<<ul<<endl;

	return 0;
}
