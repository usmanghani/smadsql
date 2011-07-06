%{
// developer: faisal
//
// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal
//
// Provides the SQL Grammar

// GRAMMAR PARSER (developer: Faisal@Nasim.org)
// $Id: sql.bison,v 1.1 2003/07/22 00:18:53 faisal Exp faisal $

#include <Base.hpp>
#include <Field.hpp>
#include <Table.h>
#include <Database.h>
#include <Statement.hpp>
#include <Function.hpp>
#include <Column.hpp>
#include <Connector.hpp>

extern Statement* st;
extern DataBase* db;
%}

%union {
	double					val;
	char				*	str;
	Table				*	tableptr;
	Column				*	colptr;
	Function			*	funcptr;
	TreeExpr			*	exprtree;
	SQLassign			*	assignexpr;
	SQLexpr				*	searchexpr;
	SQLsearch			*	searchptr;
	SQLnewfield			*	fielddef;
	SQLList<Column>		*	fieldlist;
	SQLList<Table*>		*	tablelist;
	SQLList<SQLsearch>	*	searchlist;
	SQLList<TreeExpr*>	*	exprlist;
	SQLList<SQLassign*>	*	assignlist;
	SQLList<SQLnewfield*>*	tabledef;
}

%token <val> NUM
%token <str> STRING FUNC LIT_STR LIT_STR_PARSE

%token SELECT INSERT UPDATE DELETE CREATE TABLE
%token AND NOT OR FROM WHERE INTO VALUES SET ORDER BY AS
%token IN NULLX LIKE IS SHUTDOWN ALL DISTINCT
%token INT DOUBLE CHAR TEXT ASC DESC GROUP LIMIT BETWEEN

%token TOK_NEQUAL TOK_GE TOK_LE
%token TOK_EXIT

%type <val>				field_type
%type <str>				exp_literal str
%type <tableptr>		table_name_add
%type <colptr>			column_ref
%type <funcptr>			function_ref
%type <searchptr>		search_expr
%type <tablelist>		tables_list
%type <searchlist>		search_conditions opt_where_clause
%type <fielddef>		field_definition
%type <fieldlist>		column_ref_commalist
%type <assignexpr>		scalar_exp_assign
%type <exprtree>		scalar_exp
%type <exprlist>		scalar_exp_commalist
%type <assignlist>		scalar_exp_assignlist
%type <tabledef>		table_definition

%left OR AND NOT
%left ',' '=' '>' '<' TOK_NEQUAL TOK_GE TOK_LE
%left '&' '|' '^'
%left '+' '-' '*' '/' '%'
%left NEG
%nonassoc UMINUS
%right '(' ')'

%%

language:
  main_statements
;

main_statements:
  | main_statements statement
;

statement:
	SQLstatement
  | internal_function
//  | error statement_sep { yyerrok; yyclearin; }
;

SQLstatement:
	select_statement
	| insert_statement
	| update_statement
	| create_statement
	| delete_statement
;

internal_function:
	shutdown_statement		{ exit ( (int) 0 ); }
	| TOK_EXIT 				{ exit ( (int) 0 ); }
;

selection:
	scalar_exp_commalist	{}
	| '*'
;

opt_all_distinct:
		/* empty */
	|	ALL
	|	DISTINCT
;

//	SELECT opt_all_distinct selection
select_statement:
	SELECT opt_all_distinct scalar_exp_commalist
	FROM tables_list
	opt_where_clause
	opt_order_by_clause
	opt_group_by_clause
	opt_limit_clause
	{
		st->tables = $5;
		st->fields = $3;
		//st.search=$6;

		//( Table* table , SQLList <SQLexpr*>* lst , SQLList<Column*>* fields , SQLList<SQLsearch*>* search );
		SMADdbConnector::SelectRecord ( st->tables->at(0) , $3 , st->fieldlist , st->search , st->output );
	}
;

insert_statement:
	INSERT INTO table_name_add '(' scalar_exp_commalist ')' VALUES '(' scalar_exp_commalist ')'
	{ /* SMADdbConnector::InsertRecord ()  */ }

	| INSERT INTO table_name_add SET scalar_exp_assignlist
	{
		SMADdbConnector::InsertRecord ( $3 , $5 );
	}
;

update_statement:
	UPDATE table_name_add
	SET scalar_exp_assignlist
	WHERE search_conditions
;

create_statement:
	CREATE TABLE STRING '(' table_definition ')'
	{
		if ( SMADdbConnector::CreateTable ( db , $3 , $5 ) )
		{
			cerr << "SERVER> TABLE ALREADY EXISTED... NOT CREATED\n";
		}
	}
;

delete_statement:
	DELETE FROM table_name_add
	opt_where_clause
	{
		SMADdbConnector::DeleteRecord ( $3 , st->search )
	}
;

shutdown_statement:
	SHUTDOWN {}
;

opt_where_clause:
	{$$=NULL};
	| WHERE search_conditions { $$ = $2; }
;

opt_limit_clause:
	| LIMIT NUM			{}
;

opt_order_by_clause:
	|	ORDER BY ordering_spec_commalist
;

ordering_spec_commalist:
		ordering_spec
	|	ordering_spec_commalist ',' ordering_spec
;

ordering_spec:
		INT			opt_asc_desc		{}
	|	column_ref	opt_asc_desc		{}
;

opt_asc_desc:
		/* empty */
	|	ASC
	|	DESC
;

opt_group_by_clause:
	|	GROUP BY column_ref_commalist
;

table_name_add:
	exp_literal		{ $$ = db->GetTable ( $1 ); }
;

tables_list:
	table_name_add							{ $$ = new SQLList<Table*>; $$->push ($1); }
	| tables_list ',' table_name_add		{ $$->push ($3); }
;

table_definition:
	field_definition						{ $$ = new SQLList<SQLnewfield*>; $$->push ($1); }
	| table_definition ',' field_definition { $$->push ( $3 ); }
;

field_definition:
	STRING field_type						{ $$ = new SQLnewfield ( static_cast <int> ($2) , $1 ); }
;

field_type:
	INT										{ $$ = TYPE_INTEGER;	}
	| DOUBLE								{ $$ = TYPE_DOUBLE;		}
	| CHAR									{ $$ = TYPE_SMALLCHAR;	}
	| TEXT									{ $$ = TYPE_TEXT;		}
;

search_conditions:
	{}
	| search_conditions	AND	search_conditions		{ st->search->push (new SQLsearch(1,0,0)); }
	| search_conditions	OR	search_conditions		{ st->search->push (new SQLsearch(2,0,0)); }
	| search_conditions	AND	NOT search_conditions	{ st->search->push (new SQLsearch(3,0,0)); }
	| search_conditions	OR NOT search_conditions	{ st->search->push (new SQLsearch(4,0,0)); }
	| '(' search_conditions ')'						{ $$ = $2; }
	| search_expr {
		//$$ = new SQLList<SQLsearch*>;
		$1->type = 0;
		st->search->push ($1);
	}
;

search_expr:
		scalar_exp '='			scalar_exp 		{ $$ = new SQLsearch (0,$1,$3,'='); }
	|	scalar_exp TOK_NEQUAL	scalar_exp		{ $$ = new SQLsearch (0,$1,$3,'!'); }
	|	scalar_exp '>'			scalar_exp 		{ $$ = new SQLsearch (0,$1,$3,'>'); }
	|	scalar_exp '<'			scalar_exp 		{ $$ = new SQLsearch (0,$1,$3,'<'); }
	|	scalar_exp TOK_GE		scalar_exp 		{ $$ = new SQLsearch (0,$1,$3,'G'); }
	|	scalar_exp TOK_LE		scalar_exp		{ $$ = new SQLsearch (0,$1,$3,'L'); }
	|	scalar_exp IN			scalar_exp_commalist { $$ = new SQLsearch (0,$1,$3,'I'); }
	|	scalar_exp BETWEEN		scalar_exp AND scalar_exp { $$ = new SQLsearch (0,$1,$3,'B'); }
;

scalar_exp:
		scalar_exp '+' scalar_exp		{ $$ = new TreeExpr ( new SQLexpr (1,0,'+') , $1 , $3 ); }
	|	scalar_exp '-' scalar_exp		{ $$ = new TreeExpr ( new SQLexpr (1,0,'-') , $1 , $3 ); }
	|	scalar_exp '*' scalar_exp		{ $$ = new TreeExpr ( new SQLexpr (1,0,'*') , $1 , $3 ); }
	|	scalar_exp '/' scalar_exp		{ $$ = new TreeExpr ( new SQLexpr (1,0,'/') , $1 , $3 ); }
	|	scalar_exp '%' scalar_exp		{ $$ = new TreeExpr ( new SQLexpr (1,0,'%') , $1 , $3 ); }
	|	'-' scalar_exp %prec NEG		{ $$ = new TreeExpr ( new SQLexpr (1,0,'_') , $2 , $2 ); }
	|	'(' scalar_exp ')'				{ $$ = $2; }
	|	NUM								{ $$ = new TreeExpr ( new SQLexpr (0, (int) $1) ); }
	|	str								{ SQLexpr* e = new SQLexpr(); e->type=0; e->subtype=2; e->ptr=$1; $$ = new TreeExpr (e); }
	|	column_ref						{ SQLexpr* e = new SQLexpr (2,10); e->ptr = $1; $$ = new TreeExpr (e); }
	|	function_ref					{ SQLexpr* e = new SQLexpr (3,10); e->ptr = $1; $$ = new TreeExpr (e); }// SQLexpr* e = new SQLexpr (3,1000); e->ptr = $1; $$ = new TreeNode<SQLexpr*> ( e ); }
;

scalar_exp_commalist:
		scalar_exp								{ $$ = new SQLList<TreeExpr*>; $$->push ($1); }
	|	scalar_exp_commalist ',' scalar_exp		{ $$->push ($3); }
;

scalar_exp_assignlist:
		scalar_exp_assign							{ $$ = new SQLList<SQLassign*>; $$->push ($1); }
	|	scalar_exp_assignlist ',' scalar_exp_assign	{ $$->push ($3); }
;

scalar_exp_assign:
	column_ref '=' scalar_exp					{ $$ = new SQLassign ( $1 , $3 ); }
;

column_ref:
		STRING									{ Column* C = new Column (db,NULL,$1); st->fieldlist->push(C); $$ = C; }
	|	STRING '.' STRING						{ Column* C = new Column (db,db->GetTable ($1),$3); st->fieldlist->push(C); $$ = C; }
;

column_ref_commalist:
		column_ref								{}
	|	column_ref_commalist ',' column_ref		{}
;

function_ref:
	STRING '(' scalar_exp_commalist ')'			{ $$ = new Function($1,$3); }
;

exp_literal:
	STRING
	| str
;

str:
  LIT_STR_PARSE    { $$ = $1; }
  | LIT_STR        { $$ = $1; }
;

%%
