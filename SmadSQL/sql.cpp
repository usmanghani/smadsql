// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal
//
// Provides SQL level routines

// sql.cpp (developer: Faisal@Nasim.org)
// $Id: sql.cpp,v 1.1 2003/07/15 07:29:46 faisal Exp faisal $

#include <base.hpp>
#include <strstrea.h>

#include <SQLList.hpp>
#include <Database.h>
#include <Table.h>
#include <Statement.hpp>
#include <Column.hpp>
#include <Functions.hpp>
#include <Function.hpp>
#include <SQL.hpp>

// needs to be redone
int ReduceTree ( SQLList<SQLexpr*>* tokens )
{
//	SQLList<int> mystack2;
//	SQLList<SQLexpr*>* newlist = new SQLList<SQLexpr*>;

	/*while ( ! tokens->empty () )
	{
		SQLexpr* t = tokens->quepop ();
		if ( t->type == 1 )
		{
			switch ( t->token )
			{
			case '+': mystack2.push ( mystack2.pop ()+mystack2.pop () ); break;
			case '*': mystack2.push ( mystack2.pop ()*mystack2.pop () ); break;
			case '/': mystack2.push ( mystack2.pop ()/mystack2.pop () ); break;
			case '-': mystack2.push ( mystack2.pop ()-mystack2.pop () ); break;
			}
		}
		else
		{
			if ( t->type == 0 )	mystack2.push (t->value);
			if ( t->type == 2 )	mystack2.pop ();
		}
		newlist->insert ( t );
	}*/
	//cout << endl << mystack2.top();

//	*tokens = *newlist;
	return 1;
}


///////////////////////////////////////////////////////////////////////////////
////////////////// RECURSE TREE PARSING FOR EXPRESSION BUILDING ///////////////
///////////////////////////////////////////////////////////////////////////////

SQLvariant* ParseTree ( TreeExpr* node , SMAD_RECORD* lookup )
{
	SQLList<SQLvariant*> mystack;
	int res = RecurseTree ( node , mystack , lookup );
	switch ( res )
	{
		case SMAD_ERROR:
			return 0;
		default:
		case SMAD_OK:
			return new SQLvariant ( *mystack.pop() );
	}
}

int RecurseTree ( TreeExpr* node , SQLList<SQLvariant*>& mystack , SMAD_RECORD* lookup )
{
	if ( node == 0 ) { return SMAD_OK; }
	SQLexpr* e = node->val;
	if ( RecurseTree ( node -> r , mystack , lookup ) == SMAD_ERROR ) return SMAD_ERROR;
	if ( RecurseTree ( node -> l , mystack , lookup ) == SMAD_ERROR ) return SMAD_ERROR;

	if ( e->type==1 )
	{
		if ( e->token == '+' || e->token == '*' || e->token == '-' || e->token == '/' || e->token == '_' )
		{
			SQLvariant* a = mystack.pop();
			SQLvariant* b = mystack.pop();
			double result = 0;
			double i = a->toVALUE () , j = b->toVALUE ();

			// CRASHING HERE!
			//			delete a; delete b;

			switch (e->token)
			{
				case '+': result = i+j; break;
				case '-': result = i-j; break;
				case '*': result = i*j; break;
				case '/': result = (j==0?0:i/j); break;
				case '%': result = static_cast<double> ( static_cast<int> (i) % static_cast<int> (j) ); break;
				case '_': result = -i; break;
			}
			SQLvariant* r = new SQLvariant;
			r->type = 0;
			r->val = new double (result);
			mystack.push (r);
		}
	}
	if ( e->type == 0 )
	{
		SQLvariant* S = new SQLvariant();
		S->type = 0;
		S->val = 0;

		switch ( e->subtype )
		{
		// integer or double
		case 0:
		case 1:
			S->type = 0;
			S->val = new double ( e->value );
			break;
		
		// string
		case 2:
			S->type = 1;
			S->str = strdup ( (char*) e->ptr );
//				cout << "STRING:<" << (char*) e->ptr << ">";
//				mystack.push ( atof ( (char*) e->ptr ) );
			break;
		}
		mystack.push (S);
	}

	// column reference, lookup using lookup table
	if ( e->type == 2 )
	{
		char* name = ((Column*)e->ptr)->name;

#if SMAD_DEBUG_LEVEL&4
//		cerr << "COL LOOKUP: " << name << "\n";
#endif

		SQLvariant* S = 0;

		if ( lookup != 0 )
		{
			if ( lookup->find (name) == lookup->end () )
			{
				S = new SQLvariant;
				S->type = 0;
				S->val = new double(0);
//				cerr << "DATA: " << (*lookup) [name]->toSTRING();
//				SMADerror ("Whoops.... Column NOT found!");
//				return SMAD_ERROR;
			}
			S = (*lookup) [name];
		}
		if ( S == 0 )
		{
				S = new SQLvariant;
				S->type = 0;
				S->val = new double(0);
		}
		mystack.push ( S );
	}
	// function
	if ( e->type == 3 )
	{
		Function* f = (Function*) e->ptr;
		SQLvariant* result = new SQLvariant;
		if ( f->expr->Count() )
		{
			SQLList<SQLvariant*> params;
			for (unsigned int i=0;i<f->expr->Count();i++)
				params.push ( ParseTree (f->expr->at(i) , lookup ) );

			int res = SQLFunctions::CallFunction ( f->name , *result , &params );
			if ( res == SMAD_ERROR )
			{
				SMADerror ( result->str );
				return SMAD_ERROR;
			}
		}
		mystack.push ( result );
//		cerr << "FUNCTION '" << f->name << "' RESULT: " << result->toSTRING() << "\n" << flush;
	}
	return SMAD_OK;
}


////////////////////////////////////
// Stack-based search parser
int ParseSearchExpression ( SQLList<SQLsearch*>* ptr , SMAD_RECORD* lookup )
{
	SQLList<int*> resultstack;

	for (unsigned int i=0;i<ptr->Count();i++)
	{
		int res = 0;
		SQLsearch* s = ptr->at(i);
		if ( s->type == 0 )
		{
			SQLvariant *lv = 0 , *rv = 0;
			lv = ParseTree (s->ltree , lookup);

			// Check to see whether its a single right node expression
			if ( ! s->rtree && s->rnodes )
			{
				// woosh, we got multiple nodes!
				switch ( s->OP )
				{
				case 'I':
					res = 0;
					for ( unsigned int i = 0 ; i < s->rnodes->Count() ; i++ )
					{
						rv = ParseTree ( s->rnodes->at(i) , lookup );
						if ( lv->compare (rv) == 0 )
						{
							res = 1;
							break;
						}
						delete rv;
					}
				case 'B':

				default:
					SMADerror ( "WHOOPS, unknown multi-node search operator!" );
					return SMAD_ERROR;
				}
			
			}
			else
			{
				rv = ParseTree (s->rtree , lookup);

				if ( ! lv || ! rv )
				{
					SMADerror ( "Expression parsing failed!" );			
					return SMAD_ERROR;
				}

				int comp = lv->compare (rv);

				switch (s->OP)
				{
					case '=': if ( comp == 0 ) res = 1; break;
					case '!': if ( comp != 0 ) res = 1; break;
					case '<': if ( comp  < 0 ) res = 1;	break;
					case '>': if ( comp  > 0 ) res = 1;	break;
					case 'G': if ( comp >= 0 ) res = 1;	break;
					case 'L': if ( comp <= 0 ) res = 1;	break;
				}

#if SMAD_DEBUG_LEVEL & 4
//			cout << "LVALUE: " << lv->toSTRING() << endl << flush;
//			cout << "OP: " << (char)s->OP << endl;
//			cout << "RVALUE: " << rv->toSTRING() << endl << flush;
//			cout << "RES: " << res << " (comp code: " << comp << ")";
//			cout << endl << endl;
#endif
			}

			resultstack.push ( new int ( res ) );
		
//			delete lv;
			//delete rv;
		}
		else
		{
			switch ( s->type )
			{
				case 1: resultstack.push ( new int(-1) ); break;
				case 2: resultstack.push ( new int(-2) ); break;
				case 3: resultstack.push ( new int(-3) ); break;
				case 4: resultstack.push ( new int(-4) ); break;
			}
		}
	}

	SQLList<int*> res;
	while ( ! resultstack.empty () )
	{
		int i = *resultstack.quepop ();
		if ( i < 0 )
		{
			// rvalue is popped first
			int val2 = *res.pop() , val1 = *res.pop ();
			int r = 0;
			if		( i == -1 ) r = val1 && val2;
			else if ( i == -2 ) r = val1 || val2;
			else if ( i == -3 ) r = val1 && ! val2;
			else if ( i == -4 ) r = val1 || ! val2;
			res.push ( new int ( r ) );
		}
		else res.push ( new int ( i ) );
	}
	
	//for ( unsigned int i = 0 ; i < res.Count() ; i++ )
	//	cout << ":: " << *res.at(i) << endl;
	return *res.at(0);
}




//////////////////////////////////////////////
///////////////// DEPRECATED /////////////////
//////////////////////////////////////////////


double ParseNumberTree ( TreeExpr* node )
{
	SQLList<double*> mystack;
	RecurseNumberTree ( node , mystack );
	return *mystack.pop ();
}

void RecurseNumberTree ( TreeExpr* node , SQLList<double*>& mystack )
{
	if ( node == 0 ) { return; }
	SQLexpr* e = node->val;
	RecurseNumberTree ( node -> r , mystack );
	RecurseNumberTree ( node -> l , mystack );

	if ( e->type==1 )
	{
		if ( e->token == '+' || e->token == '*' || e->token == '-' || e->token == '/' || e->token == '_' )
		{
			double i = *mystack.pop (); double j = *mystack.pop ();
			double res = 0;
			switch (e->token)
			{
				case '+': res = i+j; break;
				case '-': res = i-j; break;
				case '*': res = i*j; break;
				case '/': res = j==0?0:i/j; break;
				case '%': res = static_cast<double> ( static_cast<int> (i) % static_cast<int> (j) ); break;
				case '_': res = -i; break;
			}
			mystack.push ( new double (res) );
		}
	}
	if ( e->type == 0 )
	{
		switch (e->subtype)
		{
			case 2:
//				cout << "STRING:<" << (char*) e->ptr << ">";
				mystack.push ( new double ( atof ( (char*) e->ptr ) ) );
				break;
			default: mystack.push ( new double ( e->value ) );
		}
	}
	if ( e->type == 2 )
	{
		cerr << "COLUMN: " << ((Column*)e->ptr)->name << "\n";
		mystack.push ( new double ( 0 ) );
	}
	if ( e->type == 3 )
	{
		Function* f = (Function*) e->ptr;
		SQLvariant result;

		if ( f->expr->Count() )
		{
			SQLList<SQLvariant*> params;
			for (unsigned int i=0;i<f->expr->Count();i++)
			{
				SQLvariant* S = new SQLvariant;
				S->val = new double (ParseNumberTree (f->expr->at(i)));
				params.push ( S );
			}
			SQLFunctions::CallFunction ( f->name , result , &params );
		}
		mystack.push ( new double ( *result.val ) );
		cerr << "FUNCTION '" << f->name << "' RESULT: " << result.val << "\n" << flush;
	}
}



/*
// incomplete
int ParseSearchBuffer ( SQLList<SQLsearch*>* tokens )
{
	SQLList<int*> mystack2;
	while ( ! tokens->empty () )
	{
		SQLsearch* t = tokens->pop ();
//		if ( t->type == 1 ) mystack2.push ( mystack2.pop ()+ mystack2.pop () );
//		else if ( t->type == 2 ) mystack2.push ( mystack2.pop () * mystack2.pop () );
//		else if ( t->type == 0 ) mystack2.push (t->value - '0');
	}
	cout << endl << mystack2.top();
	return 1;
}


// useless now, as we are using TREE now
int ParseExpressionStack ( SQLList<SQLexpr*>* mylist )
{
	SQLList<SQLexpr*>* tokens = mylist->GetCopy();
	SQLList<int*> mystack2;
	while ( ! tokens->empty () )
	{
		SQLexpr* t = tokens->quepop ();
		if ( t->type > 0 )
		{
			int res = 0;
			if		( t->token == '+' ) res = *mystack2.pop ()+ *mystack2.pop ();
			else if ( t->token == '*' ) res = *mystack2.pop ()* *mystack2.pop ();
			else if ( t->token == '/' ) res = *mystack2.pop ()/ *mystack2.pop ();
			else if ( t->token == '-' ) res = *mystack2.pop ()- *mystack2.pop ();
			mystack2.push ( new int ( res ) );
		}
		else mystack2.push ( new int ( t->value ) );
	}
	cout << endl << *mystack2.top();
	return 1;
}





/////////////////////////////////////
// Tree-based search parser
SQLcondition* ParseSearchTree ( SQLcondition* ptr )
{
	SQLList<int*> resultstack;

	ParseSearchTree (ptr->ltree);
	ParseSearchTree (ptr->rtree);

	if ( s->type == 0 )
	{
		SQLsearch* s = ptr->at(i);

		SQLvariant *lv = ParseTree (s->ltree) , *rv = ParseTree (s->rtree);
		if ( ! lv || ! rv )
		{
			SMADerror ( "Expression parsing failed!" );			
			return SMAD_ERROR;
		}

		int res = 0;
		int comp = lv->compare (rv);
		
		switch (s->OP)
		{
			case '=': if ( comp == 0 ) res = 1; break;
			case '!': if ( comp != 0 ) res = 1; break;
			case '<': if ( comp  < 0 ) res = 1;	break;
			case '>': if ( comp  > 0 ) res = 1;	break;
			case 'G': if ( comp >= 0 ) res = 1;	break;
			case 'L': if ( comp <= 0 ) res = 1;	break;
		}

		cout << "LVALUE: " << lv->toSTRING() << endl << flush;
		cout << "OP: " << (char)s->OP << endl;
		cout << "RVALUE: " << rv->toSTRING() << endl << flush;
		cout << "RES: " << res << " (comp code: " << comp << ")";
		cout << endl << endl;

		resultstack.push ( new int ( res ) );
	}
	else
	{
		switch ( s->type )
		{
			case 1: resultstack.push ( new int(-1) ); cout << "AND\n" << flush; break;
			case 2: resultstack.push ( new int(-2) ); cout << "OR\n" << flush; break;
		}
	}

	return SMAD_OK;
}
*/
