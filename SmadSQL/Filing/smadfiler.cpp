#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>

#include "smadfiler.h"

extern "C"{

	int SMADFiler::append(const char* buffer, unsigned int num_bytes){
		setpos(0,SMAD_POS_END);
		return this->write(buffer,num_bytes);
	}

	SMADFiler::~SMADFiler(){
		if(this->is_open) this->close();
	}

	int SMADFiler::getbyte(){
		char aux_byte;
		this->read(&aux_byte,1);
		return aux_byte;
	}
	int SMADFiler::putbyte(int byte){
		this->write((char*)&byte, 1);
		return byte;
	}


	bool SMADFiler::isopen(){
		return this->is_open;
	}

	SMADFiler::SMADFiler(const char* filename, int omode, int pmode){
		this->open(filename,omode,pmode);
	}
	SMADFiler::SMADFiler(const char* filename, int omode){
		this->open(filename,omode);
	}

	SMADFiler::SMADFiler(const SMADFiler& ob){
		_dup2(handle,ob.handle);
		this->is_open=ob.is_open;


	}

	SMADFiler& SMADFiler::operator=(const SMADFiler& ob){
		_dup2(handle,ob.handle);
		this->is_open=ob.is_open;
		return *this;
	
	}

/*
int SMADFiler::create(const char* filename, int pmode){
	return handle=_creat(filename, pmode);

}
*/

	int SMADFiler::eof(){
		return _eof(handle);
	}

	int SMADFiler::open(const char* filename, int omode){
		this->handle=_open(filename,omode);
		if(handle!=-1) this->is_open=true;
		return this->handle;


	}

	int SMADFiler::open(const char* filename, int omode, int pmode){
		this->handle=_open(filename,omode,pmode);
		if(handle!=-1) this->is_open=true;
		return this->handle;
	

	}

	int SMADFiler::write(const char* buffer, unsigned int num_bytes){
		return _write(handle,(const void*)buffer,num_bytes);
	}

	int SMADFiler::read(char* buffer, unsigned int num_bytes){
		return _read(handle,(void*)buffer,num_bytes);
	}

	int SMADFiler::close(){
		this->is_open=false;
		return _close(handle);

	}

	int SMADFiler::commit(){
		return _commit(handle);
	}


	int SMADFiler::gethandle(){
		return this->handle;
	}


	int SMADFiler::peekbyte(){
		char aux_byte;
		this->read((char*)&aux_byte,1);
		this->setpos(-1,SMAD_POS_CUR);
		return aux_byte;
	}

	long SMADFiler::getpos(){
		return _tell(handle);
	}

	long SMADFiler::setpos(long offset, int origin){

		return _lseek(handle,offset,origin);
	}

}
