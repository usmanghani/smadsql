// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal
//
// Sets several base types for internal use

#ifndef __SQL_BASETYPES_HPP
#define __SQL_BASETYPES_HPP

#include <string>
#include <vector>
#include <map>
#include <SQLList.hpp>
#include <strstrea.h>

template <class T> class TreeNode
{
public:
	TreeNode ()		{ l = 0; r = 0; }
	TreeNode (T v)	{ val = v; l = 0; r = 0; }
	TreeNode (T v,TreeNode*l, TreeNode*r) { val = v; this->l = l; this->r = r; }
	~TreeNode () { delete val; delete l; delete r; }

	T val;
	TreeNode *l , *r;
};

template <class T> class SQLtree
{
public:
	TreeNode<T>* root;
};

class SQLvariant
{
public:
	int				type; // 0 = NUM, 1 = STRING
	unsigned int	size;
	double*			val;
	char*			str;

	//char* getStr () { return str; }
	//void  setStr (char* s) { str = strdup ( s ); }

	SQLvariant () { str = 0; val = 0; }
	SQLvariant (int t,double v)	{ type=t; val=new double(v); str=0; }
	SQLvariant (int t,char* s)	{ type=t; val=0; str=new char[strlen(s)+1]; strcpy(str,s);}
	~SQLvariant () {
		if (val!=0) delete val;
		if (str!=0) delete str;
	}

	double toVALUE ()
	{
		switch (type)
		{
		case 0: return val == NULL ? 0 : *val;
		case 1: return str == NULL ? 0 : atof ( str );
		}
		return 0;
	}

	char* toSTRING ()
	{
		ostrstream o;
		char* p = 0 , *ptr = 0;
		switch (type)
		{
		case 0:
			if ( val == NULL ) return "";
			o << *val << ends;
			p = o.str();
			ptr = new char [strlen (p)+1];
			strcpy ( ptr , p );
			return ptr;
			//return (char*) strdup ( o.str () );
			break;
		case 1: return str == NULL ? "" : str;
		}
		return "";
	}

	// compares the value based on this->type
	// returns: -1, 0 ,1 in case of less than, equal to and greater than
	int compare ( SQLvariant* p )
	{
		if ( this->type == 0 || p->type == 0 )
		{
			double val1 = this->toVALUE();
			double val2 = p->toVALUE();
			if ( val1 < val2 ) return -1;
			else if ( val1 > val2 ) return 1;
			else return 0;
		}
		else
			return strcmp ( this->toSTRING() , p->toSTRING() );
	}
};

class SQLexpr
{
public:
	int		type;		// 0 = CONSTANT, 1=Token, 2=Column ref, 3=Function
	int		subtype;	// for CONSTANTS, 0=INT, 1=SMADDOUBLE, 2=CHAR*
	char	token;
	int		value;
	void*	ptr; // pointer to colref, funcref etc.

	SQLexpr()					{ type = 0; subtype=0; value = 0; ptr = 0; }
	SQLexpr(int t,int v)		{ type = t; subtype = 0; value = v; ptr = 0; }
	SQLexpr(int t,int v,char c) { type = t; subtype = 0; value = v; token = c; ptr = 0; }
	~SQLexpr ()					{ delete ptr; }
//	SQLexpr(int t,int v,void*p) { type=t; value=v; ptr=p; }
};

typedef TreeNode<SQLexpr*> TreeExpr;

class SQLsearch
{
public:
	int	type; //SQLFIELD=0
	char OP;
	TreeExpr* ltree , *rtree;

	// for search parameters with multiple right nodes
	// example IN(), BETWEEN() etc.
	SQLList<TreeExpr*>* rnodes;

	SQLsearch () { type = -1; ltree = 0; rtree = 0; rnodes = 0; }
	SQLsearch (int t,TreeExpr*l,TreeExpr*r) { type = t; ltree = l; rtree = r; rnodes = 0; }
	SQLsearch (int t,TreeExpr*l,TreeExpr*r,char o) { type = t; ltree = l; rtree = r; OP=o; rnodes = 0; }
	SQLsearch (int t,TreeExpr*l,SQLList<TreeExpr*>*r,char o) { type = t; ltree = l; rtree = 0; rnodes = r; OP=o; }
	~SQLsearch () { delete ltree; delete rtree; delete rnodes; }
};

class Column;

class SQLassign
{
public:
	Column* field;
	TreeExpr* expr;

	SQLassign () { field = 0; expr = 0; }
	SQLassign (Column*c , TreeExpr*e) { field = c; expr = e; }
	~SQLassign () { delete expr; }
};

struct SQLnewfield
{
	int type;
	char* name;
	SQLnewfield () { type = -1; name = 0; }
	SQLnewfield (int type,char*name) { this->type=type; this->name = strdup (name); }
	~SQLnewfield () { delete name; }
};

/*
class SQLcondition
{
public:
	char type;	//& | L !
	SQLsearch* ltree , *rtree;
	SQLcondition (char t,SQLsearch*l,SQLsearch*r) { type = t; ltree = l; rtree = r; }
	~SQLcondition () { delete ltree; delete rtree; }
};
*/

typedef std::map<string,SQLvariant*> SMAD_RECORD;

#endif