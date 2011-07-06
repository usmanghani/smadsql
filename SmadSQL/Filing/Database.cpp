#include "glblinc.h"
#include "data_objects.h"

Table*	DataBase::GetTable	(char* name)
{
	return open_table (name);
}


bool DataBase::table_exists(const string& tablename) const {
	    // this routine uses the fact that if the table does not
	    //exist the map member fn find will point to the end of 
	    // map. the return value is a boolean indicating whether
	    //it is pointing to the end.
		return tables.find(tablename)!=tables.end();
}

bool DataBase::is_table_open(const string& tablename) const {
	if (open_tables.find(tablename)==open_tables.end()) return false;
	return true;
}

DataBase::~DataBase(){
	/*map<string,Table>::const_iterator iter;
	for(iter=open_tables.begin();iter!=open_tables.end();iter++){
		iter->second.tblfile.close();
		iter->second.idxfile.close();
	}*/
	map<string,Table*>::iterator iter;
	for(iter=tables.begin();
	iter!=tables.end();iter++)
		// call destructor for each table for cleanup
		// didnt call for open_tables cz is a
		// subset of the tables list;

		delete iter->second;
	/*
	dbfile.clear(0);
	dbfile.flush();
	dbfile.close();
	*/
	dbfile.commit();
	dbfile.close();


}

int DataBase::create_table(const string& tablename,const vector<FIELD_DEF>& vec){	// check if the table already exists

    if(table_exists(tablename)) return TABLE_ALREADY_EXISTS;
	//if not then create a new one
	Table* tbl=new Table;
	tbl->name=tablename;  
	
	// add it to the list of tables of the database
	tables[tablename]= tbl;
	string s1,s2;
	//these are the names of the table data and 
	// index file names
    s1=tablename+TBL_FILE_EXT;
	//index filename
	s2=tablename+IDX_FILE_EXT;
	// this file name is for the table definition
	string s3=tablename+TBL_DEF_FILE_EXT;

	tables[tablename]->filename=s1;
	tables[tablename]->idxfilename=s2;
	tables[tablename]->deffilename=s3;
	
    //open and close these files so that the OS 
	// creates them
/*
	tables[tablename]->tblfile.open(s1,ios::binary|ios::app|ios::out|ios::in);
	tables[tablename]->tblfile.close();
    tables[tablename]->idxfile.open(s2,ios::binary|ios::app|ios::out|ios::in);
	tables[tablename]->idxfile.close();
	tables[tablename]->deffile.open(s3,ios::binary|ios::app|ios::out|ios::in);
*/	
	/*
	int fh=_creat(s1.c_str(),_S_IREAD|_S_IWRITE);
	_close(fh);
     fh=_creat(s2.c_str(),_S_IREAD|_S_IWRITE);
	_close(fh);
     fh=_creat(s3.c_str(),_S_IREAD|_S_IWRITE);
	 */
	// create and open the table file
	 tables[tablename]->tblfile.open(s1.c_str(),SMAD_O_RDWR|SMAD_O_BINARY|SMAD_O_CREATE,SMAD_S_RDWR);
	 tables[tablename]->tblfile.close();
	 tables[tablename]->idxfile.open(s2.c_str(),SMAD_O_RDWR|SMAD_O_BINARY|SMAD_O_CREATE,SMAD_S_RDWR);
	 tables[tablename]->idxfile.close();
	 tables[tablename]->deffile.open(s3.c_str(),SMAD_O_RDWR|SMAD_O_BINARY|SMAD_O_CREATE,SMAD_S_RDWR);
	 /*
	 tables[tablename]->deffile.open(s3.c_str(),ios::binary|ios::out|ios::in);

	 tables[tablename]->deffile.seekp(0,ios::beg);
*/
	//write the name of the table to start of the file
	//tblfile.write(tablename.c_str(),tablename.length()+1);
	tables[tablename]->deffile.write(tablename.c_str(),tablename.length()+1);

	tables[tablename]->num_recs=0;
    tables[tablename]->rec_size=0;
	tables[tablename]->num_del_recs=0;
	for(long i =0;i<MAX_DEL_RECS;i++)
		tables[tablename]->deleted_recs[i]=-1;

	vector<FIELD_DEF>::const_iterator iter;
	// this loop calculates the size of the record
    for(iter=vec.begin();iter!=vec.end();iter++)
		tables[tablename]->rec_size+=iter->type;
    tables[tablename]->deffile.write((char*)&tables[tablename]->num_recs,sizeof(tables[tablename]->num_recs));
	tables[tablename]->deffile.write((char*)&tables[tablename]->rec_size,sizeof(tables[tablename]->rec_size));
	tables[tablename]->deffile.write((char*)&tables[tablename]->num_del_recs,sizeof(tables[tablename]->num_del_recs));
	tables[tablename]->deffile.write((char*)&tables[tablename]->deleted_recs,sizeof(tables[tablename]->deleted_recs));
      // write the field definitions to the table
	  //definition file
	for(iter=vec.begin();iter!=vec.end();iter++){
		tables[tablename]->deffile.write((char*)iter->name.c_str(),iter->name.length()+1);
		tables[tablename]->deffile.write((char*)&iter->type,sizeof(iter->type));

	}
	tables[tablename]->deffile.commit();
	tables[tablename]->deffile.close();

//	tables[tablename]->deffile.clear(0);
//	tables[tablename]->deffile.flush();
//  tables[tablename]->deffile.close();
//	fstream dbfile;
//	dbfile.open(DBLIST::MapDBtoFileName(this->name),ios::binary|ios::app|ios::out|ios::in);
    dbfile.setpos(0,SMAD_POS_END);
//	dbfile.clear();
	// first we write the name of the table
	dbfile.write(tablename.c_str(),tablename.length()+1);
	//then write the name of the table definition file
	dbfile.write(s3.c_str(),s3.length()+1);
	//then write the name of the file that contains 
	// the table data
	dbfile.write(s1.c_str(),s1.length()+1);
    // then write the name of the file that contains 
	// the index
	dbfile.write(s2.c_str(),s2.length()+1);
//	dbfile.close();
//	dbfile.clear();
//    dbfile.flush();
	dbfile.commit();


	return SMAD_NO_ERROR;

}


DataBase::DataBase(const char* s){
	//call the appropriate method to do the job
	open(string(s));
}
DataBase::DataBase(const string& s){
	//call the appropriate method to do the job
	open(s);
}

int DataBase::open(const string& s){
	name=s;
	// first map the db name to its corresponding 
	// filename. its there in the dblist
	filename=DBLIST::MapDBtoFileName(s);
	  
//	fstream dbfile(aux_file_name,ios::out|ios::binary|ios::in|ios::app);
//	dbfile.open(filename.c_str(),ios::binary|ios::out|ios::in);
	dbfile.open(filename.c_str(),SMAD_O_BINARY|SMAD_O_RDWR);

//	if(!dbfile.is_open()) return DB_FILE_CANT_BE_OPENED;
	if(!dbfile.isopen()) return DB_FILE_CANT_BE_OPENED;

	Table* tbl=new Table;
	string aux_tbl_name;
	string aux_tbl_def_file_name;
	string aux_tblfile_name;
	string aux_idxfile_name;
   // read in the name of the database
//	for(char ch=dbfile.get();ch && !dbfile.eof();){
//		name+=ch;
//		ch=dbfile.get();
//	}
//	dbfile.clear();
	while(!dbfile.eof()){
		// read in the table name
		for(char ch=(char)dbfile.getbyte();ch && !dbfile.eof();){
			aux_tbl_name+=ch;
			ch=(char)dbfile.getbyte();
		}
//		dbfile.clear();
			//read in the definition filename 
		for(ch=(char)dbfile.getbyte();ch && !dbfile.eof();){
			aux_tbl_def_file_name+=ch;
			ch=(char)dbfile.getbyte();
		}
//		dbfile.clear();
		//read in the table filename 
		for(ch=(char)dbfile.getbyte();ch && !dbfile.eof();){
			aux_tblfile_name+=ch;
			ch=(char)dbfile.getbyte();
		}
//		dbfile.clear();
		// read in the index filename 
		for(ch=(char)dbfile.getbyte();ch && !dbfile.eof();){
			aux_idxfile_name+=ch;
			ch=(char)dbfile.getbyte();
		}
//        dbfile.clear();
		tbl->name=aux_tbl_name;
		tbl->deffilename=aux_tbl_def_file_name;
		tbl->filename=aux_tblfile_name;
		tbl->idxfilename=aux_idxfile_name;
		tables[aux_tbl_name]=tbl;
		aux_tbl_name.resize(0);
		aux_tbl_def_file_name.resize(0);
		aux_tblfile_name.resize(0);
		aux_idxfile_name.resize(0);
	}
//	dbfile.close();
//	dbfile.clear();

	dbfile.commit();

	return SMAD_NO_ERROR;
}

const string& DataBase::GetName() const {
	return name;
}

const map<string,Table*>& DataBase::get_tables() const{
/*	vector<Table> vec;
	map<string,Table>::const_iterator iter;
	for(iter=tables.begin();iter!=tables.end();iter++)
		vec.push_back(iter->second);
	return vec;
	*/
    return tables;

}
// it returns a map containing the open tables
const map<string,Table*>& DataBase::get_open_tables() const {

	return open_tables;
}


Table* DataBase::open_table(const char* s){
	return this->open_table(string(s));
}

Table* DataBase::open_table(const string& s){
	//check if the table really exists
    if(tables.find(s)==tables.end()){
	//	SMADError(TABLE_DOES_NOT_EXIST, "Table does not exist");
		return NULL;
	}
    // if its already open then return a pointer 
	// to it
	if(open_tables.find(s)!=open_tables.end()) return open_tables[s];
    // else create a new one and call its open method
//	Table* aux=new Table;
//	aux->SetName(string(s));
//	int err_code=aux->open();
//	if(err_code!=SMAD_NO_ERROR) return NULL;
//  open_tables[s]=aux;
	int err_code=tables[s]->open();
	if(err_code!=SMAD_NO_ERROR) return NULL;
	open_tables[s]=tables[s];
	return open_tables[s];

	
/*
	aux->SetFileName(tables[s]->filename);
	aux->SetName(s);

	string aux_tbl_name;
	string aux_fld_name;
	enum fld_typ aux_fld_typ;
	FIELD_DEF aux_fld;
	ifstream tblfile(tables[s]->c_str(),ios::flags|ios::binary|ios::in);
	
	
	for (char ch=tblfile.get();ch && !tblfile.eof();){
		aux_tbl_name+=ch;
		ch=tblfile.get();
	}
	
	tblfile.read((char*)&aux->num_recs,sizeof(aux->numrecs));
	tblfile.read((char*)&aux->rec_size,sizeof(aux->rec_size));
    // this loop reads in the filed name and its type
	while (!tblfile.eof()){
		// this loop reads in the field name 
		for (ch=tblfile.get();ch && !tblfile.eof();){
			aux_fld_name+=ch;
			ch=tblfile.get();
		}
        //this stmt reads in the field type in the fld_typ type
		// variable 
		tblfile.read((char*)&aux_fld_typ,sizeof(enum fld_typ));
        aux_fld.name=aux_fld_name;
		aux_fld.type=aux_fld_typ;
        aux->PutField(aux_fld);
	}
	open_tables[s]=aux;
	string tblfilename,idxfilename;
	tblfilename=s+string(".SMAT");
	idxfilename=s+string(".SMAI");
    open_tables[s]->tblfile.open(tblfilename,ios::in|ios::app|ios::binary);
	open_tables[s]->idxfile.open(idxfilename,ios::binary|ios::in|ios::app);
	
	return &open_tables[s];
*/

}
