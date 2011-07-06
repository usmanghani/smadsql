#ifndef __RECORDSET_H
#define __RECORDSET_H
class RECORDSET{
	vector<RECORD> records;
//	vector<RECORD>::iterator internal_ptr;
	unsigned long internal_rec_ptr;

//	unsigned long internal_record_counter;
	unsigned long num_recs;
public:
   RECORDSET();
//   ~RECORDSET();
   RECORDSET(const vector<RECORD>& recs);
   unsigned long GetRecordCount() const;
   RECORD& GetRecord(unsigned long rec_num)const;
   void PutRecord(const RECORD& rec);
   RECORD& FetchRecord() ; 
   void sort_ascending( const string& fieldname);
   void sort_descending( const string& fieldname);
   void ResetCounter();
   std::ostream& DumpRecordSet(std::ostream&);

};
#endif
