#include "data_objects.h"
#include "glblinc.h"


class cmp_fn_asc{
private:
	string fldname;
public:
    cmp_fn_asc(const string& str){
		fldname=str;
	}

	bool operator()( RECORD& op1,  RECORD& op2){
		return op1.GetValue(fldname)<op2.GetValue(fldname);
	}
};


class cmp_fn_dsc{
private:
	string fldname;
public:
    cmp_fn_dsc(const string& str){
		fldname=str;
	}

	bool operator()( RECORD& op1,  RECORD& op2){
		return op1.GetValue(fldname)>op2.GetValue(fldname);
	}
};
/*
RECORDSET::~RECORDSET(){
		vector<RECORD>::iterator iter;
		for(iter=records.begin();iter!=records.end();iter++)
			iter->~RECORD();
	}
*/
RECORDSET::RECORDSET():num_recs(0),internal_rec_ptr(0)
	{


}

RECORDSET::RECORDSET(const vector<RECORD>& recs):num_recs(recs.size())
		{
		copy(recs.begin(),recs.end(),records.begin());
		internal_rec_ptr=0;


}
unsigned long RECORDSET::GetRecordCount() const  {
		return records.size();
	}

RECORD& RECORDSET::GetRecord(unsigned long rec_num) const { 
		return const_cast<class RECORD&>(records[rec_num]);

}
void RECORDSET::PutRecord(const RECORD& rec){
		records.push_back(rec);
		num_recs++;
//		cout<<rec;
}
	//fifo like functionality 
	// fetches the record in a linear order

RECORD& RECORDSET::FetchRecord()  {
	if (internal_rec_ptr>=num_recs) ResetCounter();

	return records[internal_rec_ptr++];


}

void RECORDSET::sort_ascending(const string& fieldname){
	sort(records.begin(),records.end(),cmp_fn_asc(fieldname));
}
void RECORDSET::sort_descending(const string& fieldname){
	sort(records.begin(),records.end(),cmp_fn_dsc(fieldname));
}
void RECORDSET::ResetCounter(){
//	internal_record_counter=0;
	internal_rec_ptr=0;


}

ostream& RECORDSET::DumpRecordSet(ostream& os){
	vector<RECORD>::const_iterator iter=records.begin();
	while(iter!=records.end()){
		os<<*iter<<endl;
		iter++;
	}
	return os;

}
