/*
 * dialog.h
 *
 *  Created on: 28 mars 2022
 *      Author: thierry
 */

#ifndef DIALOG_H_
#define DIALOG_H_

/**********************************************THIS SECTION CAN BE MODIFIED*******************************************/

#define DLG_WINDOW_TITLE_STR	    	("C-Controls")
#define DLG_WINDOW_WIDTH			    (900)
#define DLG_WINDOW_HEIGHT		    	(900)
#define DLG_WINDOW_COLOR_BACKGND	    (SDL_Color){210,210,210,255}

#define DLG_FPS         		    	(30)

#define DLG_FONT_FILE_NAME_STR	        ("./Resources/Fonts/arial.ttf")
#define DLG_FONT_SIZE    	            (20)

#define DLG_CONTROL_TEXT_LABEL_ID       (100)
#define DLG_CONTROL_LINE_EDIT_ID        (200)
#define DLG_CONTROL_BUTTON_ID        	(300)
#define DLG_CONTROL_LISTBOX_ID        	(400)

/********************************************************************************************************************/



/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*                                          DONT MODIFY CODE BELOW                                                  */
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef enum e_controlStatus{
	STATUS_CLEARED 			= 0x00000000,
	STATUS_DISABLED			= 0x00000000,       /* ALL FLAGS AT 0 :  CONTROL IS DISABLED AT STARTUP                 */
	STATUS_ENABLED 			= 0x00000001,       /* CONTROL IS ENABLED AT STARTUP                                    */
	STATUS_HIDDEN 			= 0x00000002,       /* CONTROL IS HIDDEN AT STARTUP                                     */
	STATUS_READONLY			= 0x00000004,		/* CONTROL IS READONLY AT STARTUP                                   */
	STATUS_FOCUSED 			= 0x00000008,       /* CONTROL IS FOCUSED AT STARTED : ONLY ONE MUST BE FOCUSED AT ONCE */
	STATUS_HOVERED			= 0x00000010,       /* CONTROL IS HOVERED (SHOULD'NT BE USED AT INITIALIZATION)         */
	STATUS_PRESSED			= 0x00000020,       /* CONTROL IS PRESSED AT STARTUP                                    */
    STATUS_TAB_STOPPED      = 0x00000040,       /* CONTROL CAN BE TAB STOPPED                                       */
	STATUS_RIGHT_JUSTIFIED	= 0x00000080,       /* TEXT CONTROL IS RIGHT JUSTIFIED                                  */
	STATUS_CENTERED			= 0x00000100,       /* TEXT CONTROL IS CENTERED         (DEFAULT IS LEFT JUSTIFIED)     */
	STATUS_CANT_FOCUSED		= 0x00020000,       /* CONTROL CANNOT BE FOCUSED                                        */
}t_controlStatus;

/**
 * @brief The control type enumeration for
 *        dialog control creation.
 */
typedef enum e_controlTypes{
    CONTROL_TYPE_NONE           = 0,
    CONTROL_TYPE_LINE_EDIT,             /* Text line edit       */
    CONTROL_TYPE_TEXT_LABEL,            /* Text label           */
    CONTROL_TYPE_PUSH_BUTTON,           /* Push button          */
    CONTROL_TYPE_LISTBOX,               /* Simple text list box */
}t_controlType;

/**
 * @brief Dialog box type definition.
 *        Opaque structure.
 */
typedef struct s_dialog t_dialog;

/**
 * @brief  Function pointer definition for control callback action.
 */
typedef void(*t_pCallbackFunc)(t_dialog*pDialog, int controlID, void*pApp);

/**
 * @brief Create a modal dialog box.
 *
 * @param [in] iWidth   dialog box width
 * @param [in] iHeight  dialog box height
 * @param [in] pTitle   dialog box title
 * @param [in] pApp     pointer to the associated application entity
 * @return t_dialog*    pointer to the dialog box entity
 */
t_dialog*DialogNew(int iWidth, int iHeight, char*pTitle, void*pApp);

/**
 * @brief Destroy a modal dialog box.
 *
 * @param [in] pDialog  pointer to the modal dialog box entity do destroy
 * @return t_dialog*    NULL pointer
 */
t_dialog*DialogDel(t_dialog*pDialog);

/**
 * @brief Runs the modal dialog box entity.
 *
 * @param [in] pDialog pointer to the modal dialog box entity do run
 * @return int EXIT_SUCCESS or EXIT_FAILURE
 */
int DialogDoModal(t_dialog*pDialog);

/**
 * @brief Create an insert a new control in the modal dialog bowx entity.
 *
 * @param [in] pDialog          pointer to the modal dialog box entity to wich to add control
 * @param [in] controlType      enumerate control type to create
 * @param [in] controlID        control identifier, must be unic
 * @param [in] uStatus          initial status flags of the control
 * @param [in] iLeft            left coordinate of the top-left corner of the control frame
 * @param [in] iTop             top coordinate of the top-left corner of the control frame
 * @param [in] iWidth           width of the control frame
 * @param [in] iHeight          height of the control frame
 * @param [in] colorBackgnd_R   Red component of RGBA background color of the control frame
 * @param [in] colorBackgnd_G   Green component of RGBA background color of the control frame
 * @param [in] colorBackgnd_B   Blue component of RGBA background color of the control frame
 * @param [in] colorBackgnd_A   Alpha component of RGBA background color of the control frame
 * @param [in] colorText_R      Red component of RGBA text color of the control frame
 * @param [in] colorText_G      Green component of RGBA text color of the control frame
 * @param [in] colorText_B      Blue component of RGBA text color of the control frame
 * @param [in] colorText_A      Alpha component of RGBA text color of the control frame
 * @param [in] pTitle           Title text string of the control
 * @param [in] pCallbackFunc    Callback function associate to the control
 * @return t_dialog*
 */
t_dialog*DialogNewControl(
    t_dialog*pDialog,
    const t_controlType controlType, 
    const int controlID,
	t_controlStatus uStatus,
          int iLeft,
          int iTop,
          int iWidth,
          int iHeight,
          int colorBackgnd_R,
          int colorBackgnd_G,
          int colorBackgnd_B,
          int colorBackgnd_A,
          int colorText_R,
          int colorText_G,
          int colorText_B,
          int colorText_A,
    const char*pTitle,
    t_pCallbackFunc pCallbackFunc
);

/**
 * @brief Get the title text string of the specified control by ID.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 * @return const char*      pointer to the control title text string
 */
const char*DialogControlGetTitle(const t_dialog*pDialog, const int controlID);

/**
 * @brief Set the title text string of the specified control by ID.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 * @param [in] pTitle       pointer to the title text string to set
 * @return const char*      pointer to the control title text string
 */
const char*DialogControlSetTitle(t_dialog*pDialog, const int controlID, const char*pTitle);

/**
 * @brief Do the exiting of the modal dialog box.
 *        Stop executing, and close dialog box.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 */
void DialogExit(t_dialog*pDialog);

/**
 * @brief Enabling/Disabling a control specified by his ID.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 * @param [in] enable       state enabled/disabled
 */
void DialogControlEnable(t_dialog*pDialog, const int controlID, int enable);

/**
 * @brief Checks if a control is enabled.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 * @return int 0 disabled, enabled otherwise
 */
int DialogControlIsEnabled(const t_dialog*pDialog, const int controlID);

/**
 * @brief setting//un-setting read-only status of control specified by his ID.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 * @param [in] readonly     state readonly(!=0)/or not readonly (==0)
 */
void DialogControlReadonly(t_dialog*pDialog, const int controlID, int readonly);

/**
 * @brief Checks if a control is read-only or not.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 * @return int 0 not read-only, read-only otherwise
 */
int DialogControlIsReadonly(const t_dialog*pDialog, const int controlID);

/**
 * @brief Set focus to control specified by his ID.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 */
void DialogControlSetFocus(t_dialog*pDialog, const int controlID);


/**
 * @brief Add an text string item to the control.
 *        Only for controls that allow it.
 *        Has no effect otherwise.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 * @param [in] pItem        pointer to text string item to add
 * @return char*            pointer to text string item added
 */
char*DialogControlAddItem(const t_dialog*pDialog, const int controlID, char*pItem);

/**
 * @brief Clear all items in the specified control.
 *        Only for controls that allow it.
 *        Has no effect otherwise.
 *
 * @param [in] pDialog      pointer to the dialog box entity
 * @param [in] controlID    control ID
 */
void DialogControlClear(const t_dialog*pDialog, const int controlID);

/**
 * @brief Checks if a control has no text, or no title (is empty).
 * 
 * @param [in] pDialog      pointer to the dialog box entity 
 * @param [in] controlID    control ID
 * @return int 0 not empty, empty otherwise
 */
int DialogControlIsEmpty(const t_dialog*pDialog, const int controlID);

/**
 * @brief Set control status as shown. Control is shown.
 * 
 * @param [in] pDialog      pointer to the dialog box entity 
 * @param [in] controlID    control ID
 */
void DialogControlShow(const t_dialog*pDialog, const int controlID);

/**
 * @brief Set control status as hidden. Control is hidden.
 * 
 * @param [in] pDialog      pointer to the dialog box entity 
 * @param [in] controlID    control ID
 */
void DialogControlHide(const t_dialog*pDialog, const int controlID);





#endif /* DIALOG_H_ */
