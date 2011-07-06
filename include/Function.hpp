// Developer: faisal

#ifndef __SQL_FUNCTIONHPP
#define __SQL_FUNCTIONHPP

#include <Base.hpp>

// this is the function reference holder
// not the data container
class Function
{
public:
	char*					name;
	SQLList<TreeExpr*>*		expr;

	~Function ()							{ delete expr; }
	Function ()								{ expr = 0; }
	Function (char*n)						{ name = n; expr = 0; }
	Function (char*n,SQLList<TreeExpr*>*e)	{ name = n; expr = e; }
};

#endif