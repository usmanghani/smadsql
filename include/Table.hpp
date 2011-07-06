// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: usman

#ifndef __SQL_TABLEHPP
#define __SQL_TABLEHPP

#include <SQLList.hpp>
#include <Field.hpp>
#include <fcntl.h>

class RECORD
{
public:
	std::vector<SMADVARIANT> data;
};

class RecordSet
{
	std::vector <FIELD_DEF>	FIELDS;
	std::vector <RECORD>	Records;
	unsigned long totalrecords;
public:
	unsigned long TotalRecords() { return totalrecords; }
	bool	InsertRecord	(RECORD&);
	RECORD&	GetRecord		(RECORD&);

	// FIFO like functionality
	// FetchRecord will return a record read first
	// after comparing search parameters and all
	// while ( record = RSet->FetchRecord() ) { /* blah */ }

	RECORD*	FetchRecord		(RECORD&);
	bool	Refresh();
};

class Table
{
	char* path , *name;
	std::map<std::string,FIELD_DEF*> FIELDS;

public:
	int handleStream , handleIndex;
	fstream StreamData , StreamIndex;

	unsigned long num_recs;
	unsigned long del_recs;
	unsigned long rec_size;
	bool ISOPEN;

	Table ()					{ ISOPEN = 0; }
	Table (char*n)				{ ISOPEN = 0; name=n; }
	Table (char*n,char*p)		{ ISOPEN = 0; name=n; path = p; }
	~Table ()					{ CloseTable (); }
	char* GetName ()			{ return name == NULL ? "(null)" : name; }
	char* GetPath ()			{ return path == NULL ? "(null)" : path; }
	char* SetName (char*s)		{ name = s; }
	char* SetFileName (char*s)	{ path = s; }

	RECORD&		GetRecord		(RECORD& );
	bool		InsertRecord	(const RECORD& );
	bool		UpdateRecord	(const RECORD& );
	bool		InsertRecordSet	(RecordSet &);

	bool		CloseTable		()
	{
		if ( StreamData.is_open() )		StreamData.close();
		if ( StreamIndex.is_open() )	StreamData.close();
		return true;
	}

/*	bool OpenTable (char* path)
	{
		char file [512];
		strcpy ( file , path );
		strcat ( file , ".dat" );
		handle = _open ( file , _O_RDONLY );

		strcpy ( file , path );
		strcat ( file , ".idx" );
		handleref = _open ( file , _O_RDONLY );

		ISOPEN = handle == -1 || handleref == -1 ? false : true;
		return ISOPEN;
	}
*/
/*	bool CloseTable ()
	{
		if ( ISOPEN == true )
		{
			if (handle>0)		_close (handle);
			if (handleref>0)	_close (handleref);
			return true;
		}
		return false;
	}
*/
};

#endif
