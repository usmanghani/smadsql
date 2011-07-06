#ifndef __DATA_OBJECTS_H
#define __DATA_OBJECTS_H

#include "field_def.h"
#include "glblinc.h"
#include "record.h"
#include "recordset.h"
#include "table.h"
#include "dblist.h"
#include "database.h"


/* These are the manifest constants for the error 
  codes returned by the filing routines
 */

#define SMAD_NO_ERROR						0
#define DB_LIST_FILE_CANT_BE_OPENED		1
#define DB_FILE_CANT_BE_OPENED			2
#define TABLE_DOES_NOT_EXIST			3
#define TABLE_ALREADY_EXISTS			4
#define DATABASE_ALREADY_EXISTS			5
#define DB_LIST_FILE_DOES_NOT_EXIST		6
#define WRONG_RECORD_FORMAT				7
#define RECORD_NOT_FOUND				8
#define TBL_DEF_FILE_CANT_BE_OPENED		9
#define TBL_FILE_CANT_BE_OPENED			10
#define IDX_FILE_CANT_BE_OPENED			11

//this constant defines the name of the variable to be used
// for storing the path of the dblist file
#define SMAD_ENV_VAR		"SMADPATH"
// these are the extensions for the different filetypes
// the const names are self explanatory

#define IDX_FILE_EXT		".SMAI"
#define TBL_FILE_EXT		".SMAT"
#define DB_FILE_EXT			".SMAD"
#define TBL_DEF_FILE_EXT	".DEF"



#endif

