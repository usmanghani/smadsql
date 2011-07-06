// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal
//
// Provides basic startup routines

// sql.cpp (developer: Faisal Nasim)
// $Id: main.cpp,v 1.1 2003/07/15 07:29:46 faisal Exp faisal $

#include <Base.hpp>
#include <strstrea.h>
#include <Functions.hpp>
#include <Server.hpp>
#include <Database.h>
#include <Statement.hpp>
#include <RecordSet.h>
#include <DBList.h>
#include <SQL.hpp>
#include <Connector.hpp>
#include <enumdef.h>
#include <field_def.h>
#include <vector>

using std::vector;

#define	yyFlexLexer SMADFlexLexer
#include <FlexLexer.h>

FlexLexer* lexer = NULL;
Statement* st;
DataBase* db;

int			ProcessStatement	( char* str , int len , Server& S , Client& C );
char*		SQLProcess			( char* sql );

int main ( int argc , char* argv[] , char** env )
{
	Server S;
	unsigned int port = 6000;

	SQLFunctions::LoadFunctions();
	putenv ( "SMADPATH=c:\\tmp\\smadsql\\test.db" );
	if ( DBLIST::InitDBlist () )
	{
		cerr << "DOOMED> Couldn't initialize database list.";
		return 0;
	}

	db = new DataBase;
	if ( db->open("exampledb") )
	{
		DBLIST::CreateNewDataBase("exampledb");
		db->open ( "exampledb" );
	}

/*	SQLProcess ( "CREATE TABLE mytable1 (age INT,name CHAR)" );
	SQLProcess ( "INSERT INTO mytable1 SET aage=25+1,name=CONCAT('F. ','BING BONG')" );
	return 1;
*/

//	SQLProcess ( "SELECT name,age FROM mytable1 WHERE age=19 OR age>34" );

	if ( argc > 1 ) port = atoi ( argv [1] );
	S.SetPort (port);
	S.DebugOn ();
	S.SetHandler ( ProcessStatement );
	S.StartServer ();

	//istream* x = new istrstream ("SELECT name,age,phone FROM table1,table2 WHERE (name='faisal' AND age>'16' AND phone='32' AND (status='owner' OR status='power'))" );
/*
	istream* x = new istrstream ("1+(2+3)" );
	lexer =  new SMADFlexLexer ( x , &cout); SMADparse();
	cout << st.treenode->val->value << endl;
	cout << st.treenode->r->r->val->value << endl;
	cout << "ANS: " << ParseNumberTree ( st.treenode );
	return 0;
*/

//	istream* x = new istrstream ("3+(5+8)*2" );


	// Search expression reduces to:
	// ( ( 1 AND 1 ) OR 1 ) AND 1 == 1!!! correct
	SQLProcess ( "\
		SELECT age+2,phone \
		FROM table1,table2 \
		WHERE \
			( (name='faisal' AND age<'16') OR SQRT(9)>=-('32'+64) )\
			OR status='owner'\
			AND whizkid=CHOP(UPPER(CONCAT(CONCAT('fas',(14+1)),'nas','cool')),10)\
			AND (4=4 AND NOT 1=2)\
	" );


	return 0;
}

void SMADerror ( char* s )
{
	cerr << "[[ERROR: " << s << "]]" << endl << endl;
//  cerr << yytext;
  //if ( SMADtext == NULL ) SMADtext = "(null)";
	//bool isy = *SMADtext == '\n';
	//std::cerr << s << " near '" << ( isy ? "" : SMADtext ) << "' on line " << yylineno << "\n";
}

int SMADlex () { return lexer->yylex(); }

char* SQLProcess ( char* sql )
{
	delete st;
	st = new Statement;
	st->search = new SQLList<SQLsearch*>;
	st->fieldlist = new SQLList<Column*>;

	st->output = new char [1024*32];

	istream* x = new istrstream ( sql );
	if ( lexer != NULL ) delete lexer;
	lexer =  new SMADFlexLexer ( x , &cout ) ;// (x,std::cout);
	SMADparse();

	return st->output;

	/*
	cout << "===TABLE REPORTING\n" << flush;
	for (unsigned int i=0;i<st.tables->Count();i++)
        cout << st.tables->at(i)->GetName().c_str() << "=" << st.tables->at(i)->GetTableFileName().c_str() << "\n" << flush;

	cout << "===RETURN FIELDS REPORTING\n" << flush;
	for (unsigned int i=0;i<st.fields->Count();i++)
		cout << "TREE: " << ParseTree (st.fields->at(i)) ->toSTRING() << endl << flush;

	cout << "===ALL-FIELDS REPORTING (which must be fetched from the table!)\n" << flush;
	for (unsigned int i=0;i<st.fieldlist->Count();i++)
		cout << "FIELD NAME: " << st.fieldlist->at(i)->name << endl << flush;
		//cout << "TABLE/FIELD: " << st.fieldlist->at(i)->table->GetName() << st.fieldlist->at(i)->name << endl << flush;

	cout << "===SEARCH REPORTING=" << flush << st.search->Count() << "\n" << flush;
		ParseSearchExpression ( st.search );
*/
}

int ProcessStatement ( char* str , int len , Server& S , Client& C )
{
	cout << "STATEMENT: " << str << "::" << len << endl;
	char* out = SQLProcess ( str );

	C.SendData ( "OK\r\n" , 4 );
	//C.SendData ( out , strlen ( out ) );

	if ( ! stricmp ( str , "shutdown" ) )
	{
		C.SendData ( "500 SHUTTING DOWN\r\n" , 19 );
		C.Disconnect ();
		S.StopServer();
	}
	if ( ! stricmp ( str , "quit" ) )
	{
		C.SendData ("500 BYE\r\n",9); 
		C.Disconnect();
	}
	// success
	return 0;
}
