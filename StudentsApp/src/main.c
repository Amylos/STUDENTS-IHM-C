/*
 ============================================================================
 Name        : main.c
 Author      : GarnierAndrew
 Version     :
 Copyright   : Your copyright notice
 Description : IHM Student Application in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

#include<app.h>

int main(void) {
	puts("<============== ENTER STUDENTS =================>");

	t_app*pApp = AppNew();
	int res = AppRun(pApp);
	pApp = AppDel(pApp);

	puts("<============== EXIT STUDENTS =================>");
	return res;
}





/********************* TRASH *******************/



/*	DialogNewControl(pDialog,
	controlType,
	controlID,
	uStatus,
	iLeft, iTop,
	iWidth, iHeight,
	colorBackgnd_R, colorBackgnd_G, colorBackgnd_B, colorBackgnd_A,
	colorText_R, colorText_G, colorText_B, colorText_A,
	pTitle,
	pCallbackFunc)



		DialogControlSetTitle(pDialog,CTRL_ID_FIRSTNAME_LINEEDIT, DialogControlGetTitle(pDialog, CTRL_ID_EMAIL_LINEEDIT));

	DialogNewControl(pDialog,
			CONTROL_TYPE_PUSH_BUTTON,
			CTRL_ID_EXIT_PUSHBUTTON,
			STATUS_ENABLED | STATUS_CENTERED ,
			DIALOG_BOX_WIDTH-DIALOG_BOX_PADDING-100, DIALOG_BOX_HEIGHT-DIALOG_BOX_PADDING-DIALOG_BOX_CONTROL_HEIGHT,
			100, DIALOG_BOX_CONTROL_HEIGHT,
			200, 210, 210, 255,
			0,0,0,255,
			"EXIT",
			ControlCallBackFunction);

	DialogNewControl(pDialog,
			CONTROL_TYPE_PUSH_BUTTON,
			CTRL_ID_ACTION_PUSHBUTTON,
			STATUS_ENABLED | STATUS_CENTERED ,
			DIALOG_BOX_PADDING, DIALOG_BOX_HEIGHT-DIALOG_BOX_PADDING-DIALOG_BOX_CONTROL_HEIGHT,
			100, DIALOG_BOX_CONTROL_HEIGHT,
			200, 210, 210, 255,
			0,0,0,255,
			"ACTION",
			ControlCallBackFunction);

	case CTRL_ID_EXIT_PUSHBUTTON:
		DialogExit(pDialog);
		break;
	case CTRL_ID_ACTION_PUSHBUTTON:
		break;


*/
