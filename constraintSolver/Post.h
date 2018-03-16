//
// Created by Jake Close on 3/13/18.
//

#pramga once

typedef size_t Location;      // Location 0 is the null location.
typedef size_t FileOffset;
typedef union Attributes
	{
		WordAttributes Word;
		DocumentAttributes Document;
	};

class Post
	{

	public:
	 	 //What Start / End Location
		 virtual Location GetStartLocation( );
		 virtual Location GetEndLocation( );
	   virtual Attributes GetAttributes( );
		//Returns Next next delta

		//TO-DO NICK/ZANE
		 virtual Post* Next( );
		Location currentLocation;
		//*why?
		 //virtual ISR* GetIsr( );

	};


