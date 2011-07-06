// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal

#ifndef __SQL_FUNCTIONSHPP
#define __SQL_FUNCTIONSHPP

#include <Base.hpp>
#include <SQLList.hpp>

typedef SQLList<SQLvariant*>*			SMADRuntimeFuncParam;

// base class for runtime functions
class SMADRuntimeFunction
{
public:
	SQLvariant				ReturnData;
	SQLList<SQLvariant*>*	Parameters;
	int			GetParameterCount	() { return Parameters->Count(); }
	SQLvariant*	GetParameter		() { return Parameters->quepop(); }

	void RaiseError	(int code,char*str) { ReturnData.type=code;ReturnData.str=str; }
	bool ReturnLong (long x)			{ ReturnData.type=0; ReturnData.val=new double( static_cast<double> (x) ); return true; }
	bool ReturnDouble(double x)			{ ReturnData.type=0; ReturnData.val=new double(x); return true; }
	bool ReturnString		(char* str)	{ ReturnData.type=1; ReturnData.str=str; return true; }
	virtual bool Handler	()			{ RaiseError (SMAD_ERROR,"Function unimplemented"); return false; }
};

namespace SQLFunctions
{
	extern	std::map <std::string,SMADRuntimeFunction*> FUNCTABLE;
	void	LoadFunctions ();
	int		CallFunction ( char* name, SQLvariant& ret , SMADRuntimeFuncParam params );
}

#endif