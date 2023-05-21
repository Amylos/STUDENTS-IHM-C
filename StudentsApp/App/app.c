/*
 * app.c
 *
 *  Created on: 22 avr. 2022
 *      Author: Garnier
 */


#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>
#include<container.h>
#include<students.h>
#include<dialog.h>
#include<time.h>
#include<defines.h>

#include "app.h"

#define mBitsSet(f,m)		((f)|=(m))
#define mBitsClr(f,m)		((f)&=(~(m)))
#define mBitsTgl(f,m)		((f)^=(m))
#define mBitsMsk(f,m)		((f)& (m))
#define mIsBitsSet(f,m)		(((f)&(m))==(m))
#define mIsBitsClr(f,m)		(((~(f))&(m))==(m))

void _AppControlCallBackFunction(t_dialog*pDialog,int controlID,void*pParam);


enum e_statusMask{
	ST_ALL_CLEARED 			= 0x00000000,
	ST_APP_ADD				= 0x00000001,
	ST_APP_APLY				= 0x00000002,
};

struct s_app{
	uint32_t 		 m_uStatus;
	t_dialog		*m_pDialog;
	t_container		*m_pStudents;
	int				 m_position;
	FILE			*m_pFile;

};

t_app*AppNew(void){
	t_app*pApp =(t_app*)malloc(sizeof(t_app));
	assert(pApp);

	/************************** APPLICATION CORE *Students Identity*************************/

	*pApp =(t_app){
		.m_uStatus = ST_ALL_CLEARED,
		.m_pStudents = ContainerNew((t_ptfV)StudentDel),
		.m_position =0,
	};

	srand((unsigned int) time(NULL));

	/************************** GRAPHICAL IHM CONSTRUCTION ****************************/

	pApp->m_pDialog = DialogNew(DIALOG_BOX_WIDTH, DIALOG_BOX_HEIGHT,DIALOG_BOX_TITLE,pApp);

	#include "appControlDefs.c"

	return pApp;
}


t_app*AppDel(t_app*pApp){
	assert(pApp);

	ContainerDel(pApp->m_pStudents);
	pApp->m_pDialog = DialogDel(pApp->m_pDialog);
	free(pApp);
	return NULL;
}


int AppRun(t_app*pApp){
	assert(pApp);

	return DialogDoModal(pApp->m_pDialog);
}




void _AppControlCallBackFunction(t_dialog*pDialog,int controlID,void*pParam){
	t_app*pApp = (t_app*)pParam;

/*********** FOR DEBUGING THE APP *********/

	char firstname[10];
	char nickname[10];
	char date[11];
	char email[18];


	for(size_t k = 0; k<9; k++){

		if(k<8) firstname[k] = rand()%('Z'-'A' + 1)+'A';
		else firstname[k] = '\0';
	}
	for(size_t k = 0; k<9; k++){

		if(k<8) nickname[k] = rand()%('z'-'a' + 1)+'a';
		else nickname[k] = '\0';
	}
	for(size_t k = 0; k<11; k++){

		if(k<10) date[k] = rand()%('9'-'1' + 1)+'0';
		else date[k] = '\0';
		date[2] = '/';
		date[5] = '/';
	}
	for(size_t k = 0; k<18; k++){

		if(k<17) email[k] = rand()%('z'-'a' + 1)+'a';
		else email[k] = '\0';
		email[9] = '@';
	}

/****************************************/


	switch(controlID){
	case CTRL_ID_NEW_PUSHBUTTON:	/** TO CREATE A NEW STUDENTS PROFILE **/

		DialogControlHide(pDialog,CTRL_ID_NEW_PUSHBUTTON);
		DialogControlHide(pDialog,CTRL_ID_EDIT_PUSHBUTTON);
		DialogControlShow(pDialog,CTRL_ID_ADD_PUSHBUTTON);
		DialogControlShow(pDialog,CTRL_ID_CANCEL_PUSHBUTTON);

		DialogControlEnable(pDialog, CTRL_ID_NAVBACK_PUSHBUTTON, STATUS_DISABLED);
		DialogControlEnable(pDialog, CTRL_ID_NAVFRONT_PUSHBUTTON, STATUS_DISABLED);
		DialogControlEnable(pDialog, CTRL_ID_NAVNEXT_PUSHBUTTON, STATUS_DISABLED);
		DialogControlEnable(pDialog, CTRL_ID_NAVPREV_PUSHBUTTON, STATUS_DISABLED);
		DialogControlEnable(pDialog, CTRL_ID_DEBUG_PUSHBUTTON, STATUS_ENABLED);

		DialogControlReadonly(pDialog, CTRL_ID_LASTNAME_LINEEDIT, 0);
		DialogControlReadonly(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, 0);
		DialogControlReadonly(pDialog, CTRL_ID_DATE_LINEEDIT, 0);
		DialogControlReadonly(pDialog, CTRL_ID_EMAIL_LINEEDIT, 0);

		DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT,"...");
		DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, "...");
		DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT,"...");
		DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT,"...");

		break;
	case CTRL_ID_ADD_PUSHBUTTON:	/** TO SAVE THE NEW STUDENT CREATED **/

		DialogControlShow(pDialog,CTRL_ID_NEW_PUSHBUTTON);
		DialogControlShow(pDialog,CTRL_ID_EDIT_PUSHBUTTON);
		DialogControlHide(pDialog,CTRL_ID_ADD_PUSHBUTTON);
		DialogControlHide(pDialog,CTRL_ID_CANCEL_PUSHBUTTON);

		DialogControlEnable(pDialog, CTRL_ID_NAVBACK_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVFRONT_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVNEXT_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVPREV_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_DEBUG_PUSHBUTTON, STATUS_DISABLED);

		DialogControlReadonly(pDialog, CTRL_ID_LASTNAME_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_DATE_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_EMAIL_LINEEDIT, 1);

		ContainerInsertUnic(pApp->m_pStudents, (t_ptfVV)StudentUnicInsertPredicat, StudentNew(
												DialogControlGetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT),
												DialogControlGetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT),
												DialogControlGetTitle(pDialog, CTRL_ID_DATE_LINEEDIT),
												DialogControlGetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT)));

		pApp->m_position=0;

		if(ContainerCard(pApp->m_pStudents)){
			DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT,StudentGetBirthDate(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT,StudentGetEmail(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
		}


		break;

	case CTRL_ID_APLY_PUSHBUTTON:	/** TO SAVE MODIFICATION THAT HAVE BEEN MADE **/
		DialogControlShow(pDialog,CTRL_ID_NEW_PUSHBUTTON);
		DialogControlShow(pDialog,CTRL_ID_EDIT_PUSHBUTTON);
		DialogControlHide(pDialog,CTRL_ID_ADD_PUSHBUTTON);
		DialogControlHide(pDialog,CTRL_ID_APLY_PUSHBUTTON);
		DialogControlHide(pDialog,CTRL_ID_CANCEL_PUSHBUTTON);

		DialogControlEnable(pDialog, CTRL_ID_NAVBACK_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVFRONT_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVNEXT_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVPREV_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_DEBUG_PUSHBUTTON, STATUS_DISABLED);

		DialogControlReadonly(pDialog, CTRL_ID_LASTNAME_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_DATE_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_EMAIL_LINEEDIT, 1);

		if(ContainerCard(pApp->m_pStudents)){
			ContainerPopat(pApp->m_pStudents, pApp->m_position);
			ContainerInsertUnic(pApp->m_pStudents, (t_ptfVV)StudentUnicInsertPredicat, StudentNew(
														DialogControlGetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT),
														DialogControlGetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT),
														DialogControlGetTitle(pDialog, CTRL_ID_DATE_LINEEDIT),
														DialogControlGetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT)));
		}

		if(ContainerCard(pApp->m_pStudents)){
			DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT,StudentGetBirthDate(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT,StudentGetEmail(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
		}

		break;
	case CTRL_ID_EDIT_PUSHBUTTON: /** TO MODIFY STUDENTS PROFILE  **/
		if(ContainerCard(pApp->m_pStudents)){
			DialogControlHide(pDialog,CTRL_ID_NEW_PUSHBUTTON);
			DialogControlHide(pDialog,CTRL_ID_ADD_PUSHBUTTON);
			DialogControlHide(pDialog,CTRL_ID_EDIT_PUSHBUTTON);
			DialogControlShow(pDialog,CTRL_ID_APLY_PUSHBUTTON);
			DialogControlShow(pDialog,CTRL_ID_CANCEL_PUSHBUTTON);


			DialogControlEnable(pDialog, CTRL_ID_NAVBACK_PUSHBUTTON, STATUS_DISABLED);
			DialogControlEnable(pDialog, CTRL_ID_NAVFRONT_PUSHBUTTON, STATUS_DISABLED);
			DialogControlEnable(pDialog, CTRL_ID_NAVNEXT_PUSHBUTTON, STATUS_DISABLED);
			DialogControlEnable(pDialog, CTRL_ID_NAVPREV_PUSHBUTTON, STATUS_DISABLED);
			DialogControlEnable(pDialog, CTRL_ID_DEBUG_PUSHBUTTON, STATUS_ENABLED);

			DialogControlReadonly(pDialog, CTRL_ID_LASTNAME_LINEEDIT, 0);
			DialogControlReadonly(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, 0);
			DialogControlReadonly(pDialog, CTRL_ID_DATE_LINEEDIT, 0);
			DialogControlReadonly(pDialog, CTRL_ID_EMAIL_LINEEDIT, 0);
		}
		break;
	case CTRL_ID_CANCEL_PUSHBUTTON: /** TO CANCEL THE CURRENT ACTION **/
		DialogControlHide(pDialog,CTRL_ID_ADD_PUSHBUTTON);
		DialogControlHide(pDialog,CTRL_ID_APLY_PUSHBUTTON);
		DialogControlHide(pDialog,CTRL_ID_CANCEL_PUSHBUTTON);
		DialogControlShow(pDialog,CTRL_ID_NEW_PUSHBUTTON);
		DialogControlShow(pDialog,CTRL_ID_EDIT_PUSHBUTTON);

		DialogControlEnable(pDialog, CTRL_ID_NAVBACK_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVFRONT_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVNEXT_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_NAVPREV_PUSHBUTTON, STATUS_ENABLED | STATUS_CENTERED);
		DialogControlEnable(pDialog, CTRL_ID_DEBUG_PUSHBUTTON, STATUS_DISABLED);


		DialogControlReadonly(pDialog, CTRL_ID_LASTNAME_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_DATE_LINEEDIT, 1);
		DialogControlReadonly(pDialog, CTRL_ID_EMAIL_LINEEDIT,1);

		if(ContainerCard(pApp->m_pStudents)){
			DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT,StudentGetBirthDate(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT,StudentGetEmail(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
		}

		break;



	case CTRL_ID_LOAD_PUSHBUTTON: /**** TO GET STUDENTS DATA FROM A FILE ****/

		pApp->m_pFile =fopen(DIALOG_DATA_STORAGE,"r");

		int iQuit = 0;
		while(!iQuit){
			if(feof(pApp->m_pFile)) iQuit =1;
			else{
				char string[256];
				fscanf(pApp->m_pFile, "%s", string);
				DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, string);
				fscanf(pApp->m_pFile, "%s", string);
				DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, string);
				fscanf(pApp->m_pFile, "%s", string);
				DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT, string);
				fscanf(pApp->m_pFile, "%s", string);
				DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT, string);

				ContainerInsertUnic(pApp->m_pStudents, (t_ptfVV)StudentUnicInsertPredicat, StudentNew(
								DialogControlGetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT),
								DialogControlGetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT),
								DialogControlGetTitle(pDialog, CTRL_ID_DATE_LINEEDIT),
								DialogControlGetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT)));

			}
		}

		if(ContainerCard(pApp->m_pStudents)){
			ContainerPopback(pApp->m_pStudents);
			DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT,StudentGetBirthDate(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT,StudentGetEmail(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
		}

		break;
	case CTRL_ID_SAVE_PUSHBUTTON: /** TO SAVE STUDENTS DATA INTO A FILE **/

		if(ContainerCard(pApp->m_pStudents)){

			pApp->m_pFile=fopen(DIALOG_DATA_STORAGE, "w");
			ContainerParse(pApp->m_pStudents, (t_ptfVV)StudentSerializeFunc, pApp->m_pFile);
		}
		break;
	case CTRL_ID_DEL_PUSHBUTTON: /** TO DELETE A STUDENT PROFILE **/
		if(ContainerCard(pApp->m_pStudents)){
			ContainerPopat(pApp->m_pStudents, pApp->m_position);

			DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, "...");
			DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT,  "...");
			DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT, "...");
			DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT, "...");
			pApp->m_position=0;

			if(ContainerCard(pApp->m_pStudents)){
				DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
				DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
				DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT,StudentGetBirthDate(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
				DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT,StudentGetEmail(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			}
		}

		break;
	case CTRL_ID_EXIT_PUSHBUTTON:	/** TO QUIT THE APPLICATION **/
		ContainerParse(pApp->m_pStudents, (t_ptfVV)StudentPrint, NULL);
		DialogExit(pDialog);
		break;
	case CTRL_ID_DEBUG_PUSHBUTTON:	/** TO CREATE A RANDOM PROFILE **/
		DialogControlSetTitle(pDialog,CTRL_ID_LASTNAME_LINEEDIT, firstname);
		DialogControlSetTitle(pDialog,CTRL_ID_FIRSTNAME_LINEEDIT, nickname);
		DialogControlSetTitle(pDialog,CTRL_ID_DATE_LINEEDIT, date);
		DialogControlSetTitle(pDialog,CTRL_ID_EMAIL_LINEEDIT, email);
		break;

/****************** NAVIGATION BUTTONS ********************/

	case CTRL_ID_NAVBACK_PUSHBUTTON:
		if(ContainerCard(pApp->m_pStudents)){
			DialogControlSetTitle(pDialog,CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetfront(pApp->m_pStudents)));
			DialogControlSetTitle(pDialog,CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetfront(pApp->m_pStudents)));
			DialogControlSetTitle(pDialog,CTRL_ID_DATE_LINEEDIT, StudentGetBirthDate(ContainerGetfront(pApp->m_pStudents)));
			DialogControlSetTitle(pDialog,CTRL_ID_EMAIL_LINEEDIT, StudentGetEmail(ContainerGetfront(pApp->m_pStudents)));
		}
		pApp->m_position =0;
		break;

	case CTRL_ID_NAVFRONT_PUSHBUTTON:
		if(ContainerCard(pApp->m_pStudents)){
			DialogControlSetTitle(pDialog,CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetback(pApp->m_pStudents)));
			DialogControlSetTitle(pDialog,CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetback(pApp->m_pStudents)));
			DialogControlSetTitle(pDialog,CTRL_ID_DATE_LINEEDIT, StudentGetBirthDate(ContainerGetback(pApp->m_pStudents)));
			DialogControlSetTitle(pDialog,CTRL_ID_EMAIL_LINEEDIT, StudentGetEmail(ContainerGetback(pApp->m_pStudents)));
		}
		pApp->m_position = ContainerCard(pApp->m_pStudents)-1;
		break;

	case CTRL_ID_NAVPREV_PUSHBUTTON:
		if(pApp->m_position>0)	pApp->m_position--;
		if(ContainerCard(pApp->m_pStudents)){
			DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT,StudentGetBirthDate(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT,StudentGetEmail(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
		}
		break;
	case CTRL_ID_NAVNEXT_PUSHBUTTON:
		if(pApp->m_position<ContainerCard(pApp->m_pStudents)-1)	pApp->m_position++;
		if(ContainerCard(pApp->m_pStudents)){
			DialogControlSetTitle(pDialog, CTRL_ID_LASTNAME_LINEEDIT, StudentGetLastName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_FIRSTNAME_LINEEDIT, StudentGetFirstName(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_DATE_LINEEDIT,StudentGetBirthDate(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
			DialogControlSetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT,StudentGetEmail(ContainerGetat(pApp->m_pStudents, pApp->m_position)));
		}

		break;
	default:
		break;
	}

	char buffer[10];
	if(ContainerCard(pApp->m_pStudents)){

		sprintf(buffer,"%d/%d",pApp->m_position+1,ContainerCard(pApp->m_pStudents));
		DialogControlSetTitle(pDialog, CTRL_ID_PAGE_LABEL, buffer);
		DialogControlEnable(pDialog, CTRL_ID_DEL_PUSHBUTTON, STATUS_ENABLED);
	}
	else{
		sprintf(buffer,"0/0");
		DialogControlSetTitle(pDialog, CTRL_ID_PAGE_LABEL, buffer);
		DialogControlEnable(pDialog, CTRL_ID_DEL_PUSHBUTTON, STATUS_DISABLED);
	}
}

