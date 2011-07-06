// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL

#ifndef __SQL_FIELDHPP
#define __SQL_FIELDHPP

#include <base.hpp>

#define TYPE_INTEGER	0
#define TYPE_DOUBLE		1
#define TYPE_SMALLCHAR	2
#define TYPE_TEXT		3

/*enum fld_typ {
	typSMALLCHAR,
	typDOUBLE,
	typTEXT,
	typINTEGER,
	typAUTONUMBER
};

class FIELD_DEF
{
public:
	int		type;
	std::string	name;
	int		GetType()			{ return type; }
	void	settype	(int t)		{ type = t; }
};

template<class T> class FIELD
{
public:
	T data;
	char* name;
};

class SMADINTEGER	{ public: int maxlen; double toDOUBLE () { return 0; } };
class SMADDOUBLE	{ public: int maxlen; double toDOUBLE () { return 0; } };
class SMADSMALLCHAR	{ public: int maxlen; double toDOUBLE () { return 0; } };
class SMADTEXT		{ public: int maxlen; double toDOUBLE () { return 0; } };

class SMADVARIANT
{
	int type;
	SMADINTEGER*	vINTEGER;
	SMADDOUBLE*		vDOUBLE;
	SMADSMALLCHAR*	vSMALLCHAR;
	SMADTEXT*		vTEXT;

public:
	SMADVARIANT ()					{ vINTEGER = 0; vDOUBLE = 0; vSMALLCHAR =0; vTEXT = 0; }
	SMADVARIANT (SMADINTEGER*v)		{ vINTEGER = v; }
	SMADVARIANT (SMADDOUBLE*v)		{ vDOUBLE = v; }
	SMADVARIANT (SMADSMALLCHAR*v)	{ vSMALLCHAR = v; }
	SMADVARIANT (SMADTEXT*v)		{ vTEXT = v; }
	int		GetType ()				{ return type; }
	double	toDOUBLE ()
	{
		return 0;
		switch (type)
		{
			case TYPE_INTEGER:		return vINTEGER->toDOUBLE (); break;
			case TYPE_DOUBLE:		return vDOUBLE->toDOUBLE (); break;
			case TYPE_SMALLCHAR:	return vSMALLCHAR->toDOUBLE (); break;
			case TYPE_TEXT:			return vTEXT->toDOUBLE (); break;
			default:				return 0;
		}
	}
};
*/

#endif