//********************************************
//	Ini ��غ���
//********************************************

#ifndef _INI_H_
#define _INI_H_

#include "pubtool.h"

#define ERROR_DATA -99999999

#define MAX_PATH          260

//�����ļ���
class CIni
{
private:
	char m_strFileName[MAX_PATH];	//�ļ���
	long m_lDataLen;				//�ļ�����
	char* m_strData;				//�ļ�����

	int IndexNum;					//������Ŀ��[]����Ŀ��
	int *IndexList;					//������λ���б�
	int Point;						//��ǰָ��
	int Line, Word;					//��ǰ����

public:
	CIni();
	CIni(char*);							//��ʼ���������ļ�
	virtual ~CIni();						//�ͷ��ڴ�
	char *GetData();						//�����ļ�����
	int GetLines(int);						//�����ļ�������

	bool Open(char *);						//�������ļ�
	void Close();							//�ر������ļ�
	bool Save(char *filename=NULL);			//���������ļ�

private:
	void InitIndex();						//��ʼ������
	int FindIndex(char *);					//���ر���λ��
	int FindData(int, char *);				//��������λ��
	int GotoNextLine(int); 					//����
	char *ReadDataName(int &);				//��ָ��λ�ö�һ��������
	char *ReadText(int);					//��ָ��λ�ö��ַ���

	bool AddIndex(char *);					//����һ������
	bool AddData(int, char *, char *);		//�ڵ�ǰλ�ü���һ������
	bool ModityData(int, char *, char *);	//�ڵ�ǰλ���޸�һ�����ݵ�ֵ
	int GotoLastLine(char *index);			//��ָ���ƶ�����INDEX�����һ��

public:
	int ReadInt(char *, char *);			//��һ������
	int ReadInt(char *, int );				//��ָ�����ж�һ����
	char *ReadText(char *, char *);			//��һ���ַ���
	char *ReadText(char *, int);			//��ָ�����ж�һ�ַ���
	char *ReadCaption(char *, int);			//��ָ���ж�һ�ַ�����
	bool Write(char *, char *, int);		//дһ������
	bool Write(char *, char *, char *);		//дһ���ַ���
	int GetContinueDataNum(char *);			//������������������INDEX����һ�����У�
};

#endif