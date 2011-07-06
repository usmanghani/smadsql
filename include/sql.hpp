// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
//
// Header file for tree parsing

#ifndef __SQL_SQLHPP
#define __SQL_SQLHPP

#include <SQLList.hpp>
class Server;
class Client;

int			ProcessStatement	( char* str , int len , Server& S , Client& C );
int			ReduceTree			( SQLList<SQLexpr*>* tokens );
double		ParseNumberTree		( TreeExpr* );
void		RecurseNumberTree	( TreeExpr* , SQLList<double*>& );

int			RecurseTree			( TreeExpr* , SQLList<SQLvariant*>& , SMAD_RECORD* );
SQLvariant* ParseTree			( TreeExpr* , SMAD_RECORD* );
int			ParseSearchExpression ( SQLList<SQLsearch*>* , SMAD_RECORD* );

#endif

