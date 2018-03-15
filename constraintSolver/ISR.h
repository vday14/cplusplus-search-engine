//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "Post.h"

class ISR
	{

	public:
		//
		ISR* DocumentEnd;
		virtual Post* Next( );
		virtual Post* NextDocument( );
		virtual Post* Seek( Location target);
		virtual Location GetStartLocation( );
		virtual Location GetEndLocation( );
		virtual ISR *GetDocumentISR( );


	};


