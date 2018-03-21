//
// Created by Jake Close on 3/13/18.
//

#pragma  once

#include "Post.h"

class PostingList
	{
private:
	struct PostingListIndex
		{
		FileOffset Offset;
		Location PostLocation;
		};

	PostingListIndex *index;

	virtual char *GetPostingList ( );

public:
	virtual Post *Seek ( Location );


	};


