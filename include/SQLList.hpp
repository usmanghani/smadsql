// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
//
// Flexible doubly linked list implementation
// can be used for list, stack, ques etc.

#ifndef __SQL_SQLLISTHPP
#define __SQL_SQLLISTHPP

template <class T> class SQLList
{
	class MyNode
	{
	public:
		T value;
		MyNode* next , *prev;
		MyNode	()	{ value = 0; next = 0; prev = 0; }
	};

	bool deletenode (MyNode* node)
	{
		if ( node == NULL ) return false;
		if ( node->prev != NULL )
			node->prev->next = node->next;
		else first = node->next;
		if ( node->next != NULL )
			node->next->prev = node->prev;
		else last = node->prev;
		delete node;
		return true;
	}

	void deleteAllNodes ( MyNode* start )
	{
		delsubnodes (start);
		first = 0; last = first;
	}

	void delsubnodes ( MyNode* start )
	{
		if ( start->next != NULL ) delsubnodes ( start->next );
		delete start->value;
		delete start;
	}

	MyNode* getNode ( T val )
	{
		MyNode* n = new MyNode;
		t->value = val;
		return n;
	}

public:
	MyNode			*first , *last;
	SQLList ()		{ first = 0; last = first; }
	~SQLList ()		{ if (first) { deleteAllNodes(first); } }

	unsigned int Count() { unsigned int cnt=0; MyNode*i=first; while(i){i=i->next;cnt++;} return cnt; }
	int EraseAll()	{ if (first !=NULL ) { deleteAllNodes(first); return true; } else return false; }
	SQLList<T>*		GetCopy()
	{
		SQLList<T>* l = new SQLList<T>;
		for ( MyNode* t = first ; t ; t=t->next ) l->insert (t->value);
		return l;
	}

	// insert in the front
	void insertfront (T val)
	{
		if ( first != NULL )
		{
			MyNode *tmp = new MyNode;
			tmp->value = val;
			tmp->next = first;
			tmp->prev = NULL;
			first->prev = tmp;
			first = tmp;
		}
		else insert (val);
	}

	// insert to the end of the list
	void insert (T val)
	{
		MyNode* tmp = new MyNode;
		tmp->value = val;
		if ( first == NULL ) first = tmp;
		else last->next = tmp;
		tmp->next = NULL;
		tmp->prev = last;
		last = tmp;
	}

	bool empty ()		{ return first == NULL; }
	void push (T val)	{ insert (val); }
	void reverse () {
		if ( first == NULL || first == last ) return;
	}

	// STACK OPERATIONS
	T pop () { T val = last->value; deletenode (last); return val; }
	T top () { if ( last!=NULL ) return last->value; return NULL; }
	T top2 () { if ( last->prev != NULL ) return last->prev->value; return NULL; }
	T bottom () { return first->value; }

	// QUEUE OPERATIONS
	T quepop () { T val = first->value; deletenode (first); return val; }
	T quetop () { return first->value; }
	T quelast () { return last->value; }


	// extract by position
	T at (unsigned int pos)
	{
		for ( MyNode* t = first ; t ; t=t->next )
			if ( pos-- == 0 ) return (t->value);
		return NULL;
	}

	// erase by position
	bool erase (unsigned int pos)
	{
		for ( MyNode* t = first ; t ; t=t->next )
			if ( pos-- == 0 ) return deletenode ( t );
		return false;
	}

	// erase by value
	bool erase (T val)
	{
		for ( MyNode* t = first ; t ; t=t->next )
			if ( val == t ) return deletenode ( t );
		return false;
	}

/*	void printall ()
	{
		for ( MyNode* ptr = first ; ptr ; ptr = ptr->next )
			cout << "ELEMENT: " << ptr->value << endl;
	}*/
};

#endif