/*
 * SI2P, SIP based Peer-to-Peer Network Location System
 * Copyright 2005 MPRC
 * Edit by LiZang
 */
//0820

#ifndef __NODE_H__
#define __NODE_H__

#include <osip2/osip.h>
#ifndef OSIP_MT
#define OSIP_MT
#endif

#include "MyType.h"
#include "ChordId.h"
#include "FingerTable.h"
#include "constants.h"
#include "AdOsip.h"
#include "ThreadTransport.h"
#include "regapi.h"
#include "BootStraps.h"
#include "NodeState.h"
#include "uinfo.h"
#include "pipe.h"


class FingerTable ;
class ThreadTransport ;

class NodeState ;
class Node
{
private :
	/* local ChordId*/
	ChordId chordId;						
	
	/* route table */
	FingerTable			*fingerTable ;

	/*const member*/
	Constants			*constants;

	
public :
	/* used to be AF_INET for ipv4 */
	int                 ip_family;			
	char				localip[50] ;			
	char  				localport[10] ;			
	osip_list_t*		j_transactions;	
	char 				user_agent[50];
	int					expires ;
	struct	osip_mutex*	gl_lock;


	/*	used to store bootstrap	*/
	BootStrap			*j_bootstraps ;
	uinfo_t				*user_info_list;
	uinfo_t				*local_user_info_list;
	uinfo_t				*red_user_info_list;
	jpipe_t			*user_info_pipe;
	char user_contact[200];
   
public:
	/******tool function******/
	NS_EVENT ReportRCVEvent(osip_message_t *M) ;

	/*��finger���succlist�е�node��Ч*/
	void set_node_inactive(ChordId node) ;
	/*ʹ��contacts�б�������succlist*/
	void setSuccListWithContacts(osip_message_t *M,BOOL includefirst) ;
	/*ʹ��contacts�б�������pred*/
	void setPredWithContacts(osip_message_t *M) ;
	/*��chordIdת��Ϊһ��uri,���isSearchΪtrue����ChordId��ipӦ��Ϊ�գ�ע���ѯ��*/
	char* ChordId2Uri(ChordId cId ,BOOL isSearch) ;
	/**/
	ChordId getPredWithContact(osip_message_t *M) ;



public:
	//�̶߳���
	AdOsip *adosip;		
	ThreadTransport *th_transport ;
	ThreadBase *th_stabilize ;

	friend void *mythread_transport(void *arg) ;
	friend void *mythread_adosip(void *arg) ;
	friend void *mythread_stabilize(void *arg) ;
	int startthread() ;
	int StartStabilize() ;

	/* ������ݽṹ */
	int Data_toString(char **buf , unsigned int &length) ;

	/*��ʼ��*/
	int initlog(char *filename) ;
	
	void StartNode(BOOL assingle) ;
	void StartNode();
public:	
	Node(char * ip , char * port, char * ua_name) ;
	~Node() ;
	


	ChordId getChordId() ;
	void setChordId(ChordId chordId) ;
	
	
	FingerTable *getFingerTable() ;
	Constants *getConstants() ;

	/* get a bootstrap from bootstrap list */
	ChordId getABootStrap() ;

	/*the method for debug*/
	void debug() ;

	//-------------------------------------------------
	/**/
	/*start_index : Ҫ���õ�finger��� (0<= start_index <= m)
	node : ����finger��node
	return : δ���º��finger�ĵ�һ��
	*/
	int Set_Fingers(int start_index , ChordId node) ;

	/*	�ҵ�chordIdǰ��������finger 
	chordId : Ҫ������chordId
	return : chordIdǰ��������finger��Ӧ��node
	*/
	ChordId closestPrecedingFinger(ChordId k) ;

	/*���յ�ע��*/
	void OnRegister(osip_message_t *request,osip_transaction_t *tr) ;

	/*���յ�200��Ӧ*/
	void OnRegisterSuccess(osip_transaction_t * tr , osip_message *response) ;

	/*���յ�302��Ӧ
	*/
	void OnRegisterRedirect(osip_transaction_t * tr , osip_message *response) ;

	void OnRegisterTimeout(osip_transaction_t *tr);

	void OnDiscoverTimeout(osip_transaction_t *tr);

	void OnRegisterFailure(osip_transaction_t *tr,osip_message_t *response);

	/*
	*/
	int SndResponse(int status , 
		osip_message_t *request ,
		osip_transaction_t *tr,
		REG_TYPE type , 
		ChordId contact, 
		BOOL IncludeSuccList) ;

	/**/
	int SndRegister(REG_TYPE type , 
		ChordId req_uri ,			//req_uri
		ChordId to ,				//to
		ChordId contact,			//contact
		BOOL IncludeSuccList = false) ;

	void DatatoFile() ;
	void DatatoMonitor() ;
	void LogStream(const char *out) ;


public:

	/*
	[Close]--->[Inited]
	*/
	virtual void Init() ;

	/*
	[Inited]--->[Discoving]
	*/
	virtual void Discover() ;

	/*
	[Discovered]--->[Joining]
	*/
	virtual void Join() ;

	/*
	[Normal]--->[Close]
	*/
	virtual void Leave() ;

	/*
	[Normal]--->[Normal]
	*/
	virtual void stabilize() ;
public:
	void GetUserInfoFromInput(char **aor,char **contact);

	void RegisterUser(REG_TYPE type,char *aor,char *contact,char *username,char *passwd);
	
	void QueryUser();

	int SndUserRegisterRequest(REG_TYPE type,
				uinfo_t *user_info,
				const char *registrar,
				int expires);

	int SndUserRegisterResponse(int status,
				osip_message_t *request,
				osip_transaction_t *tr,
				REG_TYPE type,
				char *contact);
	int SndUserRegisterRequest(char *aor,
				const char *requri);

	int SndResponse4Query(int status,
					const char *contact,
					osip_transaction_t *tr,
					osip_message_t *request);

	void TransferUserInfoToPred(ChordId node);

	void TransferUserInfoToSucc(ChordId node);

	void PrintAllUser();

	void clearUserInfoList(uinfo_t **list);
	int GetNodeState();
private :
	friend class NodeState ;
	void ChangeState(NodeState *) ;
private :
	NodeState * _state ;

} ;

extern Node *mynode ;
#endif