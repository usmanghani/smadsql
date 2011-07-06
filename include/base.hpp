// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal

#ifndef __SQL_BASE_H
#define __SQL_BASE_H

#define SMAD_VERSION		"0.1.1"

#define SMAD_DEBUG_LEVEL 1|2
#define SMAD_OK							0
#define SMAD_WARNING					-2
#define SMAD_ERROR						-1

extern "C++"
{
	#include <iostream.h>
	#include <string.h>
	#include <fstream.h>

	#include "enumdef.h"
	#include "field_def.h"

	#include <BaseTypes.hpp>
	#include <Database.h>
	#include <Table.h>
	#include <Field.hpp>
	#include <Column.hpp>
	#include <Function.hpp>
}

//extern char*		yytext;
//extern unsigned	long yylineno;
extern int			SMADparse ();
extern void			SMADerror(char* s);
extern int			SMADlex ();

#endif
