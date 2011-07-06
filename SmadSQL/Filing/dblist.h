#ifndef __DBLIST_H
#define __DBLIST_H

class  DBLIST {
	//this data structure holds the dblist in memory
	// for fast lookup
	static map<string,string> dblist;
	// this flag tells whether the system has 
	// been initiated or not
	 static bool Initiated;
	// name of the dblistfile
	static string dblistfilename;

public:
	 static int InitDBlist();
	 static bool DBExists(const string&) ;
	 static string MapDBtoFileName(const string&);
	 static int CreateNewDataBase(const string&);
	
};

#endif
