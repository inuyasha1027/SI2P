/*
 * SI2P, SIP based Peer-to-Peer Network Location System
 * Copyright 2005 MPRC
 * Edit by LiZang
 */
//0820

#ifndef __MYTYPE_H__
#define __MYTYPE_H__

/*the type of registrations*/
enum REG_TYPE
{
	MULTICAST,			
	JOIN,				
	FINDSUCC,		
	STABILIZE,
	LEAVE,
	USER_REGISTRATION,
	TRANSFER_REGISTRATION,
	THIRD_PARTY,
	USER_QUERY,
	RED_REGISTER,
	OTHER,
} ;

enum NS_EVENT
{
	//- ACTIVE EVENT
	INIT_SND ,
	DISCOVER_SND ,
	JOIN_SND,
	LEAVE_SND ,
	STABILIZE_SND,

	//- PASSIVE EVENT
	MULTICAST_REQ_RCV,			
	MULTICAST_RESP_2XX,			

	JOIN_REQ_RCV,				
	JOIN_RESP_2XX,				
	JOIN_RESP_3XX,				

	FINDSUCC_REQ_RCV,
	FINDSUCC_RESP_2XX,
	FINDSUCC_RESP_3XX,

	STABILIZE_REQ_RCV,
	STABILIZE_RESP_2XX,

	LEAVE_REQ_RCV,

	USER_REG_RCV,
	USER_REG_RESP_2XX,
	USER_REG_RESP_3XX,

	RED_REGISTER_RCV,
	RED_REGISTER_RESP_2XX,

	USER_QUERY_RCV,
	USER_QUERY_RESP_2XX,
	USER_QUERY_RESP_3XX,

	NODE_FAILURE,
	NO_NODE_FIND,


	//- OTHER EVENT
	EVT_OTHER
};




#endif