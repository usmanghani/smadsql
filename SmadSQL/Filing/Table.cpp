#include "glblinc.h"
#include "data_objects.h"

int Table::write_record(RECORD& rec){
	if ( rec.mv.size() < field_defs.size()) return WRONG_RECORD_FORMAT;

	map<string,FIELD_DEF>::const_iterator iter;
	for(iter=field_defs.begin();
	    iter!=field_defs.end();
		iter++)
			rec.GetValue(iter->first).serialize(tblfile);
	return 0;
}

int Table::read_record(RECORD& rec){
	SMADSMALLCHAR* psc;
	SMADDOUBLE* pdbl;
	SMADINTEGER* pint;
	SMADTEXT* ptxt;

	map<string,FIELD_DEF>::const_iterator iter;
	for(iter=field_defs.begin();
	    iter!=field_defs.end();
		iter++){

			switch(iter->second.type){
			case typSMALLCHAR:
				psc=new SMADSMALLCHAR();
				psc->deserialize(tblfile);
				rec.PutValue(iter->first,SMADVARIANT(psc));
				break;
			case typTEXT:
				ptxt=new SMADTEXT();
				ptxt->deserialize(tblfile);
				rec.PutValue(iter->first,SMADVARIANT(ptxt));
				break;
				
			case typINTEGER:
				pint=new SMADINTEGER();
				pint->deserialize(tblfile);
				rec.PutValue(iter->first,SMADVARIANT(pint));
                break;

			case typDOUBLE:
				pdbl=new SMADDOUBLE();
				pdbl->deserialize(tblfile);
				rec.PutValue(iter->first,SMADVARIANT(pdbl));
                break;

			}


		}
		return 0;
}

int Table::get_recordset(RECORDSET& rset, CMPFN cmp){
//	tblfile.clear();

    RECORD aux_rec;
//	tblfile.seekg(0,ios::beg);
	tblfile.setpos(0,SMAD_POS_BEG);
//	while(tblfile.peek()!=EOF){
	for(int i=0;i<num_recs;i++){
		int err_code=get_record(aux_rec,cmp);
//		cout<<aux_rec;
		if(err_code!=SMAD_NO_ERROR) break;
		rset.PutRecord(aux_rec);
	}
//	tblfile.clear();
	return SMAD_NO_ERROR;
}

void Table::SetName(const string& newname){
	name=newname;
}
string Table::GetName() const{
	return name;
}

Table::~Table(){
//	tblfile.flush();
//	tblfile.close();
//	idxfile.flush();
//	idxfile.close();
//	deffile.flush();
//	deffile.close();
	tblfile.commit();
	tblfile.close();
	idxfile.commit();
	idxfile.close();
	deffile.commit();
	deffile.close();


}
int Table::delete_record(CMPFN cmp){
//	tblfile.clear();
    int err_code;
	RECORD rec;
//	tblfile.seekg(0,ios::beg);
	// go to the start of the file 
	tblfile.setpos(0,SMAD_POS_BEG);
//	while(tblfile.peek()!=EOF){
	while(!tblfile.eof()){
		err_code=get_record(rec,cmp);
		if(err_code==RECORD_NOT_FOUND) return err_code;
		if(err_code==SMAD_NO_ERROR){
			cout<<"deleting record: "<<rec<<endl;

//			tblfile.seekg(-rec_size,ios::cur);
//			tblfile.setpos(-rec_size,SMAD_POS_CUR);
			num_del_recs++;
			--num_recs;
//			deffile.seekp(name.length()+1,ios::beg);
			deffile.setpos(name.length()+1,SMAD_POS_BEG);
			deffile.write((char*)&num_recs,sizeof(num_recs));
			for(int i=0;i<MAX_DEL_RECS;i++) 
				if(deleted_recs[i]==-1){
					deleted_recs[i]=(tblfile.getpos()-rec_size);
 					cout << "record size is: "<< rec_size<<endl;
					cout<< "deleting at position: "<<tblfile.getpos()-rec_size<<endl;
 
					
//					deffile.seekp(name.length()+1+
//						sizeof(num_recs)+sizeof(rec_size),ios::beg);
					deffile.setpos(name.length()+1+
						sizeof(num_recs)+sizeof(rec_size),SMAD_POS_BEG);

					deffile.write((char*)&num_del_recs,sizeof(num_del_recs));
//					deffile.seekp(i*sizeof(deleted_recs[i]),ios::cur);
					//deffile.setpos(i*sizeof(deleted_recs[i]),SMAD_POS_CUR);
					//deffile.write((char*)&deleted_recs[i],sizeof(deleted_recs[i]));
					deffile.write ((char*) deleted_recs, sizeof (deleted_recs));

//					deffile.flush();
					deffile.commit();
					break;

					//tblfile.setpos(rec_size,SMAD_POS_CUR);
					

				}

//			tblfile.seekg(rec_size,ios::cur);
//			tblfile.setpos(rec_size,SMAD_POS_CUR);


//		deleted_recs[num_del_recs-1]=tblfile.tellg();
		}
	}
//	tblfile.clear();
	return err_code;

}
/*
int Table::update_record( RECORD& rec, CMPFN cmp){
//	tblfile.clear();
	int err_code;
	if (rec.mv.size() > field_defs.size()) return WRONG_RECORD_FORMAT;
	map<string, FIELD_DEF>::const_iterator iter;

	RECORD aux_rec;
//	tblfile.seekg(0,ios::beg);
//	while(tblfile.peek()!=EOF){
	while(!tblfile.eof()){
		err_code=get_record(aux_rec,cmp);
		if(err_code==RECORD_NOT_FOUND) return err_code;
		if(err_code==SMAD_NO_ERROR){
//			tblfile.seekg(-rec_size,ios::cur);
			tblfile.setpos(-rec_size,SMAD_POS_CUR);
			for(iter=field_defs.begin();
			iter!=field_defs.end();iter++){
				if(rec.mv.find(iter->first)!=rec.mv.end())
					aux_rec.PutValue(iter->first,rec.GetValue(iter->first));
//					tblfile.setpos(iter->second.type,SMAD_POS_CUR);
				write_record(aux_rec);

			}
		}    						
	}
//	tblfile.clear();
	return err_code;
}
*/
/*
U need to create a function 
RECORD* GetUpdateValues(RECORD*) 
that takes an already filled record and updates the values in the 
appropriate fields
u neednt return a map<string,smadvariant> pair duh
the record does the same work
u will write
rec->PutValue(field_name, SMADVARIANT value);
the rest of the task is done
good luck

*/

int Table::update_record(CMPFN cmp){
	RECORD* rec=new RECORD();
    int err_code=NO_ERROR;

	if( rec.mv.size() > field_defs.size()) return WRONG_RECORD_FORMAT;
	tblfile.setpos(0,SMAD_POS_BEG);
	while( !tblfile.eof()){
		err_code = get_record(*rec, cmp);
		if(err_code == NO_ERROR){
			GetUpdateValues(rec);
			tblfile.setpos(-rec_size, SMAD_POS_CUR);
			write_record(*rec);
		}
	}
	delete rec;


	
}


bool Table::is_record_deleted(long ptr_to_rec){
	for (short i=0;i<MAX_DEL_RECS;i++){
		if(ptr_to_rec==deleted_recs[i]) return true;
	}
	return false;
}

	
int Table::get_record(RECORD& rec, CMPFN cmp){
	bool isfound=false;

//	tblfile.clear();
//	if(tblfile.peek()==EOF) tblfile.seekg(0,ios::beg);
	
//	tblfile.seekg(0,ios::beg);
//	RECORD rec;
//	map<string,FIELD_DEF>::const_iterator iter;
//	while(tblfile.peek()!=EOF){
	while(!tblfile.eof()){
//		iter=field_defs.begin();
		/*
		for(unsigned short s=0;s<num_del_recs;s++){
			if (tblfile.tellg()==deleted_recs[s]){
				tblfile.seekg(rec_size,ios::cur);
				continue;
			}
		}
		*/
//		if(is_record_deleted(tblfile.tellg())) {
		if(is_record_deleted(tblfile.getpos())) {
//			tblfile.seekg(rec_size,ios::cur);
			tblfile.setpos(rec_size,SMAD_POS_CUR);
			continue;
		}
		/*
        SMADSMALLCHAR* psc;
		SMADTEXT* ptxt;
		SMADINTEGER* pint;
		SMADDOUBLE* pdbl;

		while(iter!=field_defs.end()){
			switch (iter->second.type){
			case typSMADSMALLCHAR:
			    psc=new SMADSMALLCHAR;
				psc->deserialize(tblfile);
				rec.PutValue(iter->first,SMADVARIANT(psc));
				break;
			case typSMADTEXT:
				ptxt=new SMADTEXT;
				ptxt->deserialize(tblfile);
				rec.PutValue(iter->first,SMADVARIANT(ptxt));
				break;
			case typSMADDOUBLE:
				pdbl = new SMADDOUBLE;
				pdbl->deserialize(tblfile);
				rec.PutValue(iter->first, SMADVARIANT(pdbl));
				break;
			case typSMADINTEGER:
				pint=new SMADINTEGER;
				pint->deserialize(tblfile);
				rec.PutValue(iter->first,SMADVARIANT(pint));
				break;
			}
			iter++;
		}*/
	read_record(rec);
	
		if(cmp->cmp(rec)){
			isfound = true;
			break;
		}
	}

/*	
	if(tblfile.peek()==EOF && !cmp(rec)){
		tblfile.clear();
		return RECORD_NOT_FOUND;
	}
	*/
	if(tblfile.eof() && !isfound){
//		tblfile.clear();
		return RECORD_NOT_FOUND;
	}

//  tblfile.clear();

	return SMAD_NO_ERROR;
}

int Table::insert_record( RECORD& rec){
	// check whether the record format is correct
	// if the number of fields in the record to be 
	// inserted is greater than the number of fields 
	// in the table then the format is wrong 
//  tblfile.clear();
	if(rec.mv.size() > field_defs.size() ) {
	//	SMADError ("Wrong Record Format." , WRONG_RECORD_FORMAT);
		return WRONG_RECORD_FORMAT;
	}
    // go to the start of the file
//	tblfile.seekp(0,ios::beg);
//	tblfile.seekg(0,ios::beg);
	tblfile.setpos(0,SMAD_POS_BEG);

	//probe the file for deleted records
/*	while(tblfile.peek()!=EOF && is_record_deleted(tblfile.tellp())==false){
		tblfile.seekp(rec_size,ios::cur);
		tblfile.seekg(rec_size,ios::cur);
	}*/
/*	int handle=tblfile.gethandle();
	while (!_eof(handle) && is_record_deleted(_tell(handle))==false){
		_lseek(handle, rec_size, SEEK_CUR);
	}
*/
	if(this->num_del_recs>0){
	while(!tblfile.eof() && is_record_deleted(tblfile.getpos())==false){
		tblfile.setpos(rec_size,SMAD_POS_CUR);
	}


//	if(tblfile.peek()!=EOF){
	if(!tblfile.eof()){
		--num_del_recs;
		
		for(long l=0;l<MAX_DEL_RECS;l++){ 
			if (deleted_recs[l]==tblfile.getpos()){
				deleted_recs[l]=-1;
				deffile.setpos(name.length()+1+
					sizeof(num_recs)+sizeof(rec_size),SMAD_POS_BEG);
				deffile.write((char*)&num_del_recs,sizeof(num_del_recs));
				deffile.write((char*)deleted_recs, sizeof(deleted_recs));
//				deffile.setpos(l*sizeof(deleted_recs[l]),SMAD_POS_CUR);
//				deffile.write((char*)deleted_recs[l],sizeof(deleted_recs[l]));
				deffile.commit();
				break;
			}
		}
		
	}	
	//Just to make sure we are at the end if there
	// are no deleted records
    }
	else tblfile.setpos(0,SMAD_POS_END);
/*
	if(tblfile.eof()){
		tblfile.setpos(0,SMAD_POS_END);
	}
	*/
//  tblfile.clear();
	/*
	map < string , FIELD_DEF>::const_iterator iter;
	for(iter=field_defs.begin();iter!=field_defs.end();iter++){
		//  check if the corresponding field in the 
		// record to be inserted is not specified
		// meaning its intended to be empty
		if(rec.mv.find(iter->first)==rec.mv.end()){
			SMADSMALLCHAR* psc;
			SMADINTEGER* pint;
			SMADDOUBLE* pdbl;
			SMADTEXT* ptxt;

			switch(iter->second.type){
			case typSMADINTEGER:
				pint=new SMADINTEGER;
				pint->setvalue(0);
				pint->serialize(tblfile);
				delete pint;
				break;
			case typSMADDOUBLE:
				 pdbl=new SMADDOUBLE;
				pdbl->setvalue(0.0);
				pdbl->serialize(tblfile);
				delete pdbl;
				break;
			case typSMADTEXT:
				 ptxt = new SMADTEXT;
				ptxt->setvalue("");
				ptxt->serialize(tblfile);
				delete ptxt;
				break;
			case typSMADSMALLCHAR:
				 psc=new SMADSMALLCHAR;
				psc->setvalue("");
				psc->serialize(tblfile);
				delete psc;
				break;
			}

		}
		else {
			rec.GetValue(iter->first).serialize(tblfile);
		
		}
	}*/
	//tblfile.close();
	//tblfile.open(string(name+TBL_FILE_EXT).c_str(),ios::app|ios::binary|ios::in|ios::out);
//	tblfile.flush();
	write_record(rec);
	tblfile.commit();
//	tblfile.clear();
	++num_recs;
//	deffile.clear();
	deffile.setpos(name.length()+1,SMAD_POS_BEG);
//	cout<<deffile.tellp();
	deffile.write((char*)&num_recs,sizeof(num_recs));
	deffile.commit();


	return SMAD_NO_ERROR;

}

int Table::open(){
//	deffilename=name+TBL_DEF_FILE_EXT;
//	deffile.open(deffilename.c_str(),ios::binary|ios::out|ios::in);
	deffile.open(deffilename.c_str(),SMAD_O_RDWR|SMAD_O_BINARY);

	
	if(!deffile.isopen()) return TBL_DEF_FILE_CANT_BE_OPENED;
	deffile.setpos(0,SMAD_POS_BEG);
   ///read in the name of the table
	string aux_name;
	for (char ch=deffile.getbyte(); ch && !deffile.eof();){
	//	this->name+=ch;
		aux_name+=ch;
		ch=deffile.getbyte();
	}
//	deffile.clear();
	//get the number of records
	deffile.read((char*)&num_recs,sizeof(num_recs));
	// get the record size

	deffile.read((char*)&rec_size,sizeof(rec_size));
	// get the number of deleted records
	deffile.read((char*)&num_del_recs,sizeof(num_del_recs));
	// get the actual deleted records
	deffile.read((char*)deleted_recs,sizeof(deleted_recs));
    // open the index and data files
//	filename=name+TBL_FILE_EXT;
//	tblfile.open((name+TBL_FILE_EXT).c_str(),ios::binary|ios::app|ios::out|ios::in);
	tblfile.open((name+TBL_FILE_EXT).c_str(),SMAD_O_BINARY|SMAD_O_RDWR);
	if(!tblfile.isopen()) return TBL_FILE_CANT_BE_OPENED;
//  idxfilename=name+IDX_FILE_EXT;
	idxfile.open((name+IDX_FILE_EXT).c_str(),SMAD_O_BINARY|SMAD_O_RDWR);

	if(!idxfile.isopen()) return IDX_FILE_CANT_BE_OPENED;

//	string aux_fld_name;
//	enum fld_typ aux_fld_typ;
	// read in the field definitons from the
	// definition file
	struct FIELD_DEF aux_fld_def;
	while(!deffile.eof()){
		for(ch=deffile.getbyte();ch && !deffile.eof(); ){
			aux_fld_def.name+=ch;
			ch=deffile.getbyte();
		}
//		deffile.clear();
		deffile.read((char*)&aux_fld_def.type,sizeof(aux_fld_def.type));
		PutField(aux_fld_def);
//		field_defs[aux_fld_def.name]=aux_fld_def;
		aux_fld_def.name.resize(0);

	}
	return SMAD_NO_ERROR;

}	    

const map<string,FIELD_DEF>& Table::GetFields() const{
	return field_defs;
}
FIELD_DEF Table::GetField(const string& name)  {
	return field_defs[name];
}

void Table::PutField(const FIELD_DEF& fld_def){
	field_defs[fld_def.name]=fld_def;
}

string Table::GetTableFileName() const{
	return filename;
}
void Table::SetTableFileName(const string& newname){
	filename=newname;
}
string Table::GetDefFileName()const{
	return deffilename;
}
void Table::SetDefFileName(const string& s){
	deffilename=s;
}
void Table::SetIndexFileName(const string& s){
	idxfilename=s;
}
string Table::GetIndexFileName()const {
	return idxfilename;
}
