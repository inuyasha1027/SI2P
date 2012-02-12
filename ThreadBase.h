/*
 * SI2P, SIP based Peer-to-Peer Network Location System
 * Copyright 2005 MPRC
 * Edit by LiZang
 */
//0820

#ifndef __THREADBASE_H__
#define __THREADBASE_H__

#include "pipe.h"
/* ��Ҫ��ʵ���߳�֮���Э������ */

class ThreadBase
{
public:	
	void *thread;		/* thread */
	jpipe_t wakeup;		
public:
	ThreadBase() ;			//constructor
	~ThreadBase() ;			//destructor
	int ThreadRelease() ;
	int ThreadStart(void *(*func_start) (void *), void *arg) ;			//start the thread
	int ThreadWakeUp() ;		//wake up the thread 
} ;


#endif //void head recontain