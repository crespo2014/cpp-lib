//===========================================================================
//
// Module:	LNMQ.HPP
//
// Description: Class library definition for LNMessageQueue and 
//				LNMessageQueueBody
//
//===========================================================================
//
// Copyright (c) 1997 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNMQ_HPP
#define LNMQ_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

extern "C"
{
#include <string.h>

/* Notes API include files */
#include <mq.h>
#include <miscerr.h>
}

//--------------------------------------------------------------------------
// Class name:	LNMessageQueue
//
//	Description:
//
//--------------------------------------------------------------------------

class LNIMPEXPCL LNMessageQueue : public LNSmartPtr
{
friend class LNNotesSession;

public:
	LNMessageQueue();
	~LNMessageQueue();

	LNCLASSID 	GetClassID() const {return LNCLASS_LNMESSAGEQUEUE;}
	
	LNSTATUS 	Close();

	LNINT		GetMessageCount() const;

	LNSTATUS 	GetNextMessage (LNINT msglen, char *mesage, 
				    LNINT * retmsglen, LNINT timeout = 0);

	LNBOOL 		IsQuitPending() const;

	LNSTATUS 	Open();

	LNSTATUS 	PutMessage (char * message, LNINT priority = NOPRIORITY);

	void	 	Quit();

private:

	LNMessageQueue (const LNMessageQueue &other);
	LNMessageQueue& operator= (const LNMessageQueue &other);

	LNMessageQueue& operator=( LNMessageQueueBody *mqbody );

	LNSTATUS CreateMessageQueueBody( LNNotesSession *session,
		const LNString &mqname);

	LNMessageQueueBody* GetMessageQueueBody() const
			{return (LNMessageQueueBody *)Body;}

};


#endif	//LNMQ_HPP

