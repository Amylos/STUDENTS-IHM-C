/*
 * students.h
 *
 *  Created on: 22 avr. 2022
 *      Author: Garnier
 */


typedef struct s_student t_student;

t_student*StudentNew(const char*FirstName,const char*NickName,const char*BirthDate,const char*Email);

t_student*StudentDel(t_student*pIdentity);

t_student*StudentPrint(const t_student*pIdentity);

t_student*StudentInsertPredicat(t_student*pIdentityToInsert, t_student*pIdentityActual);

t_student*StudentUnicInsertPredicat(t_student*pIdentityToInsert, t_student*pIdentityActual);

t_student*StudentSerializeFunc(t_student*pIdentity, FILE*pStream);


char*StudentGetLastName(t_student*pStudent);

char*StudentGetFirstName(t_student*pStudent);

char*StudentGetBirthDate(t_student*pStudent);

char*StudentGetEmail(t_student*pStudent);

t_student*StudentUpdate(t_student*pStudent,const char* pFirstName,const char*pNickName,const char*pBirthDate,const char*pEmail);
