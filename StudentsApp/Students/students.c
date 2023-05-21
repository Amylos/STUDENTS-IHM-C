/*
 * students.c
 *
 *  Created on: 22 avr. 2022
 *      Author: Garnier
 */



#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>
#include <string.h>

#include "students.h"

enum e_statusMask{
	ST_ALL_CLEARED 		= 0x00000000,
};

struct s_student{
	uint32_t	m_uStatus;
	char		*m_pLastName;
	char 		*m_pFirstName;
	char		*m_pBirthDate;
	char		*m_pEmail;
};


t_student*StudentNew(const char*pLastName,const char*pFirstName,const char*pBirthDate,const char*pEmail){

	t_student*pStudent = (t_student*)malloc(sizeof(t_student));
	assert(pStudent);

	*pStudent = (t_student){
		.m_pLastName 	= (char*)malloc(strlen(pLastName)+1),
		.m_pFirstName  	= (char*)malloc(strlen(pFirstName)+1),
		.m_pBirthDate	= (char*)malloc(strlen(pBirthDate)+1),
		.m_pEmail     	= (char*)malloc(strlen(pEmail)+1),
	};


	strcpy(pStudent->m_pLastName, pLastName);
	strcpy(pStudent->m_pFirstName, pFirstName);
	strcpy(pStudent->m_pBirthDate, pBirthDate);
	strcpy(pStudent->m_pEmail, pEmail);

	return pStudent;
}

t_student*StudentDel(t_student*pStudent){
	assert(pStudent);

	free(pStudent->m_pLastName);
	free(pStudent->m_pFirstName);
	free(pStudent->m_pBirthDate);
	free(pStudent->m_pEmail);
	free(pStudent);

	return NULL;
}


t_student*StudentPrint(const t_student*pStudent){

	assert(pStudent);

	printf("%s\t\%s\t%s\t%s\n", pStudent->m_pLastName, pStudent->m_pFirstName,pStudent->m_pBirthDate,pStudent->m_pEmail);

	return NULL;
}

/*****************/

t_student*StudentInsertPredicat(t_student*pIdentityToInsert, t_student*pIdentityActual){
    assert(pIdentityToInsert);
    assert(pIdentityActual);
    return (t_student*)(long)(strcmp(pIdentityToInsert->m_pLastName, pIdentityActual->m_pLastName)<0);
}

t_student*StudentUnicInsertPredicat(t_student*pIdentityToInsert, t_student*pIdentityActual){
    assert(pIdentityToInsert);
    assert(pIdentityActual);

    int res=strcmp(pIdentityToInsert->m_pLastName, pIdentityActual->m_pLastName);

    if(res<0) return (t_student*)(long)1;
    else if(res>0) return NULL;
    return (t_student*)(long)-1;
}

t_student*StudentSerializeFunc(t_student*pStudent, FILE*pStream){
	fprintf(pStream, "%s\t\%s\t%s\t%s\n", pStudent->m_pLastName, pStudent->m_pFirstName,pStudent->m_pBirthDate,pStudent->m_pEmail);
	return NULL;
}


char*StudentGetLastName(t_student*pStudent){
	assert(pStudent);
	return pStudent->m_pLastName;
}

char*StudentGetFirstName(t_student*pStudent){
	assert(pStudent);
	return pStudent->m_pFirstName;
}

char*StudentGetBirthDate(t_student*pStudent){
	assert(pStudent);
	return pStudent->m_pBirthDate;
}

char*StudentGetEmail(t_student*pStudent){
	assert(pStudent);
	return pStudent->m_pEmail;
}

t_student*StudentUpdate(t_student*pStudent,const char* pFirstName,const char*pNickName,const char*pBirthDate,const char*pEmail){
	assert(pStudent);

	strcpy(pStudent->m_pLastName,pFirstName);
	strcpy(pStudent->m_pFirstName,pNickName);
	strcpy(pStudent->m_pBirthDate,pBirthDate);
	strcpy(pStudent->m_pEmail,pEmail);

	return NULL;
}



t_student* StudentSetFirstName(t_student*pStudent, char*pFirstName){
	assert(pStudent);
	strcpy(pStudent->m_pLastName,pFirstName);
	return NULL;
}


t_student* StudentSetNickName(t_student*pStudent, char*pNickName){
	assert(pStudent);
	strcpy(pStudent->m_pFirstName,pNickName);
	return NULL;
}

t_student* StudentSetBirthDate(t_student*pStudent, char*pBirthDate){
	assert(pStudent);
	strcpy(pStudent->m_pBirthDate,pBirthDate);
	return NULL;
}

t_student* StudentSetEmail(t_student*pStudent, char*pEmail){
	assert(pStudent);
	strcpy(pStudent->m_pEmail,pEmail);
	return NULL;
}

