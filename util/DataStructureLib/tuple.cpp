//
// Created by Zane Dunnings on 3/17/18.
//

// Outline of query language from Prof. Nicole Hamilton, University of Michigan 03/15/2018
//31 lines

enum TupleType
	{
	PhraseTupleType,
	OrTupleType,
	AndTupleType,
	NotTupleType,
	SearchTupleType
	};

class Tuple
	{
public:
	Tuple *Next;
	TupleType Type;
	virtual ISR *Compile( );
	Tuple ( ) : Next( nullptr )
		{
		}
	TupleList
	virtual ~Tuple( );
	};

class TupleList
	{
public:
	Tuple *Top,
			*Bottom;
	size_t Count;
	Tuple &Push( Tuple *t );
	Tuple &Push( TupleList *t );

	//modified
	Tuple &Top( );
	void Pop( );
	};


Tuple &TupleList::Push ( Tuple *t )
	{
	Bottom->Next = t;
	Bottom = t;
	++count;

	if( Top == nullptr )
		Top = Bottom;

	return &t;
	}

Tuple & TupleList::Push ( TupleList *t )
	{
	if( Top == nullptr )
		{
		Top = t->Top;
		Bottom = t->Bottom;
		count = t->count;
		return &Bottom;
		}
	else
		{
		Bottom->Next = t->Top;
		Bottom = t->Bottom;
		count += t->count;
		return &Bottom;
		}
	}

Tuple &TupleList::Top( )
	{
	return *Top;
	}

void TupleList::Pop ( )
	{
	if( Top == nullptr)
		return;

	if( Top == Bottom )
		Bottom = nullptr;

	Tuple *ptr = Top;
	Top = Top->Next;
	delete ptr;
	ptr = nullptr;
	--count;
	}