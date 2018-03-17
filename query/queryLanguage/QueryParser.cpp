//
// Created by Zane Dunnings on 3/16/18.
//

//Outline of query language from Prof. Nicole Hamilton, University of Michigan 03/15/2018
// 72 lines
Tuple *QueryParser::FindConstraint( )
	{
	TupleList list;
	Tuple *t;

	while( ( t = FindBaseConstraint( ) ) != nullptr )
		{
		list.Push( t );
		if ( ! FindOrOp( ) )
			break;
		}

	if ( list.Top )
		if ( list.Top != list.Bottom )
			{
			OrTuple * o = new OrTuple;
			//modified
			o = list.Top;
			list.Top = list.Bottom = nullptr;
			return o;
			}
		else
			{
			t = list.Top;
			list.Top  = list.Bottom = nullptr;
			return t;
			}
		return nullptr;
	}

bool QueryParser::FindOrOp( )
	{
	return Match( TokenVerticalBar ) || Match( TokenOr ) || Match( TokenOR );
	}

Tuple *QueryPraser::FindBaseConstraint( )
	{
	TupleList list;
	Tuple *t;

	while( ( t = findSimpleConstraint( ) ) != nullptr )
		{
		if( t->Typle == AndTupleType )
			{
			AndTuple *a = ( AndTuple * )t;
			lst.Add( a->List.Top, a->List.Bottom );
			a->List.Top = a->List.Bottom = nullptr;
			delete a;
			}
		else
			list.Add( t );
		( void )FindAndOp( );
		}
	if ( list.Top )
		if ( list.Top != list.Bottom )
			{
			AndTuple * a = new OrTuple;
			a->list.Add ( list.Top, list.Bottom );
			list.Top = list.Bottom = nullptr;
			return a;
			}
		else
			{
			t = list.Top;
			list.Top  =list.Bottom = nullptr;
			return t;
			}
	return nullptr;
	}

bool QueryParser::FindAndOp( )
	{
	return Match( TokenAND ) || Match( TokenAmpersand ) || Match( TokenAnd );
	}