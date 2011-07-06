#include "data_objects.h"
#include "glblinc.h"
#include "field_def.h"
// definitions for static member variables
map<string,string> DBLIST::dblist;
bool DBLIST::Initiated;
string DBLIST::dblistfilename;


int DBLIST::CreateNewDataBase(const string& name){
	// When creating a new database we just append
	// its name to the dblist file 
	// check wheteher the DB is already on the list
	// if yes then return a value indicatin that the 
	// DB exists
    if(dblist.find(name)!= dblist.end()) return DATABASE_ALREADY_EXISTS;

//    fstream out(dblistfilename.c_str(),ios::binary|ios::out|ios::in);
	smadfiler out(dblistfilename.c_str(),SMAD_O_BINARY|SMAD_O_RDWR);

	if(!out.isopen()) return DB_LIST_FILE_CANT_BE_OPENED;

/*	if(!out.is_open()) return DB_LIST_FILE_CANT_BE_OPENED;{


		int fh=_creat(dblistfile,_S_IREAD|_S_IWRITE);
		_close(fh);
		fstream out(dblistfile,ios::binary|ios::out|ios::in);
	}
*/
    // this is the name of the database
	// write it out to the dblist file

//	out.seekp(0,ios::end);
//	out.setpos(0,SMAD_POS_END);

// it is very vital to clear the eof flag
//	out.clear(0);

//	out.write(name.c_str(),name.length()+1);// 1 added for null char 
   // appending ".SMAD" to the name of the 
	// database gives us the name of the database file
    out.append(name.c_str(),name.length()+1);
    
	string aux=name+string(DB_FILE_EXT);
	// write out the name of the database file 
	out.write(aux.c_str(),aux.length()+1);
	//also add to the in_mem list.
	// if the list has been initiated
	if(Initiated)
        dblist[name]=aux;
//	out.flush();
	out.commit();

    
	out.close();
	// this is the way to create a new file

	smadfiler(aux.c_str(),SMAD_O_CREATE/*|SMAD_O_RDWR|SMAD_O_BINARY*/, SMAD_S_RDWR);


//	int _fh=_creat(aux.c_str(),_S_IREAD|_S_IWRITE);
//	_close(_fh);


	return SMAD_NO_ERROR;
}

int DBLIST::InitDBlist(){
	// this routines assumes that the path of the 
	// dblist file is the value of the env
	// var SMADPATH
	string s = "c:/dblist.lst";

	if(!s.length()){
	/*	   SMADError("DBLIST file does not exist",
			         DB_LIST_FILE_DOES_NOT_EXIST);*/
		   return DB_LIST_FILE_DOES_NOT_EXIST;
	}

	dblistfilename=s;
//	fstream dblistfile(s.c_str(),ios::binary|ios::out|ios::in);
	smadfiler dblistfile(s.c_str(),SMAD_O_RDWR|SMAD_O_BINARY);

//	if(!dblistfile.is_open()) return DB_LIST_FILE_CANT_BE_OPENED;
	if(!dblistfile.isopen()) return DB_LIST_FILE_CANT_BE_OPENED;
	
	string dbname;
//	dblistfile.seekg(0,ios::beg);
	dblistfile.setpos(0,SMAD_POS_BEG);

//	dblistfile.clear();
	while(!dblistfile.eof()){
		// get the name of the database 
		// DBNAME AND DBFILENAME ARE SEPARATED BY A 
		// NULL CHARACTER
		for(char ch=dblistfile.getbyte();ch!=0 && !dblistfile.eof();){
          dbname+=ch;
		  ch=dblistfile.getbyte();
		}
//		dblistfile.clear();
       // get the filename 
		string auxdbfilename;
		for(ch=dblistfile.getbyte();ch && !dblistfile.eof();){
		    auxdbfilename+=ch;
			ch=dblistfile.getbyte();
		}
		
		cerr << "<DB:" << dbname << '=' << auxdbfilename << ">\r\n";

		dblist[dbname]=auxdbfilename;

		dbname.resize(0);
		auxdbfilename.resize(0);


	}
//    dblistfile.clear(0);

//	dblistfile.flush();
	dblistfile.commit();

// no need to close the file ne more as the destructor takes care
// of it

//	dblistfile.close();

    Initiated=true;
	return SMAD_NO_ERROR;


}

bool DBLIST::DBExists(const string& dbname){
	// if the db exists then the length of the string 
	// will be greater then zero else it will be zero

	return dblist[dbname].length() > 0 ? true : false;
}

string DBLIST::MapDBtoFileName(const string& dbname){
	// it maps the name of the database to the 
	// filename of the database
	// at present it only means appending .SMAD to 
	// the list name of the DB
	return dblist[dbname];
}
