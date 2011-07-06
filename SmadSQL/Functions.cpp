// developer: faisal
//
// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
//
// Handles all the runtime expandable functions
// for example SELECT SQRT(col)

#include <Base.hpp>
#include <map>
#include <string>
#include <Function.hpp>

using namespace std;

#include <map>
#include <string>
#include <cmath>
#include <Functions.hpp>

map <string,SMADRuntimeFunction*> SQLFunctions::FUNCTABLE;

int SQLFunctions::CallFunction ( char* name, SQLvariant& ret , SMADRuntimeFuncParam params  )
{
	strupr ( name );
	if ( FUNCTABLE.find (name) == FUNCTABLE.end () )
	{
		string s = "Function " + string(name) + " does not exist!";
		ret.type = SMAD_ERROR;
		ret.str = (char*) s.c_str();
		return SMAD_ERROR;
	}
	SMADRuntimeFunction* f = FUNCTABLE [name];
	f->Parameters = params;
	bool status = f->Handler();
	ret = f->ReturnData; // use copy-constructor
	return status == true ? SMAD_OK : SMAD_ERROR;
}

class SMADRuntimeFunctionSQRT : public SMADRuntimeFunction
{
	bool Handler ()
	{
		if ( GetParameterCount() != 1 )
		{
			RaiseError (SMAD_ERROR,"SQRT takes only one parameter");
			return false;
		}

		SQLvariant* param = GetParameter();
		double val = param->toVALUE();
		return ReturnDouble ( sqrt (val) );
	}
};


class SMADRuntimeFunctionCONCAT : public SMADRuntimeFunction
{
	bool Handler ()
	{
		if ( GetParameterCount() < 1 )
		{
			RaiseError (SMAD_ERROR,"CONCAT takes atleast one parameter");
			return false;
		}
		ostrstream o;
		for (unsigned int i=0;i<Parameters->Count();i++)
			o << Parameters->at(i)->toSTRING();
		o << ends;

		return ReturnString ( o.str () );
	}
};



class SMADRuntimeFunctionUPPER : public SMADRuntimeFunction
{
	bool Handler ()
	{
		if ( GetParameterCount() != 1 )
		{
			RaiseError (SMAD_ERROR,"UPPER takes only one parameter");
			return false;
		}

		SQLvariant* param = GetParameter();
		char* str = param->toSTRING();
		char* ptr = str;
		while ( (*ptr=toupper(*ptr++)) && *ptr);
		return ReturnString ( str );
	}
};

class SMADRuntimeFunctionLOWER : public SMADRuntimeFunction
{
	bool Handler ()
	{
		if ( GetParameterCount() != 1 )
		{
			RaiseError (SMAD_ERROR,"LOWER takes only one parameter");
			return false;
		}

		SQLvariant* param = GetParameter();
		char* str = strdup ( param->toSTRING() );
		char* ptr = strdup ( str );
		while ( (*ptr=tolower(*ptr++)) && *ptr);
		return ReturnString ( str );
	}
};

class SMADRuntimeFunctionLENGTH : public SMADRuntimeFunction
{
	bool Handler ()
	{
		if ( GetParameterCount() != 1 )
		{
			RaiseError (SMAD_ERROR,"LENGTH takes only one parameter");
			return false;
		}

		SQLvariant* param = GetParameter();
		return ReturnDouble ( strlen ( param->toSTRING() ));
	}
};

class SMADRuntimeFunctionCHOP : public SMADRuntimeFunction
{
	bool Handler ()
	{
		if ( GetParameterCount() != 2 )
		{
			RaiseError (SMAD_ERROR,"CHOP takes two parameters");
			return false;
		}

		SQLvariant* param1 = GetParameter ();
		SQLvariant* param2 = GetParameter ();

		char* ptr = param1->toSTRING ();
		int	len = static_cast <int> ( param2->toVALUE() );
		
		if ( (int) strlen ( ptr ) > (int) len ) ptr [len] = 0;
		return ReturnString ( ptr );
	}
};

class SMADRuntimeFunctionEXAMPLE : public SMADRuntimeFunction
{
	bool Handler ()
	{
		// Make sure the parameters we have received
		// are in correct number
		if ( GetParameterCount() != 1 )
		{
			RaiseError (SMAD_ERROR,"EXAMPLE takes only one parameter");
			return false;
		}

		// Fetch the parameter
		SQLvariant* param = GetParameter();
		
		// Return a number with the length of the string
		return ReturnLong ( strlen ( param->toSTRING() ));
	}
};

void SQLFunctions::LoadFunctions ()
{
	FUNCTABLE ["SQRT"] = (SMADRuntimeFunction*) new SMADRuntimeFunctionSQRT;
	FUNCTABLE ["CONCAT"] = (SMADRuntimeFunction*) new SMADRuntimeFunctionCONCAT;
	FUNCTABLE ["UPPER"] = (SMADRuntimeFunction*) new SMADRuntimeFunctionUPPER;
	FUNCTABLE ["LOWER"] = (SMADRuntimeFunction*) new SMADRuntimeFunctionLOWER;
	FUNCTABLE ["LENGTH"] = (SMADRuntimeFunction*) new SMADRuntimeFunctionLENGTH;
	FUNCTABLE ["CHOP"] = (SMADRuntimeFunction*) new SMADRuntimeFunctionCHOP;

	// EXAMPLE FUNCTION FOR DEVELOPERS
	FUNCTABLE ["EXAMPLE"] = (SMADRuntimeFunction*) new SMADRuntimeFunctionEXAMPLE;
}
