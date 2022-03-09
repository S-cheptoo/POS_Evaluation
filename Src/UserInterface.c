#include "sdk_tplus.h"
#include "GL_GraphicLib.h"
#include "TlvTree.h"
#include "GTL_Assert.h"


#include "UserInterface.h"


//****************************************************************************
//      EXTERN
//****************************************************************************
extern T_GL_HGRAPHIC_LIB hGoal; // Handle of the graphics object library

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

////  variables ///////////////////////////////////////////

static T_GL_HGRAPHIC_LIB __EMV_UI_goalHandle = NULL;	//!< The GOAL handle.
static Telium_File_t *__EMV_UI_displayDriver = NULL;			//!< The display driver handle.
static Telium_File_t *__EMV_UI_keyboardDriver = NULL;			//!< The keyboard driver handle.
static Telium_File_t *__EMV_UI_touchDriver = NULL;				//!< The touch screen driver handle.

//// Functions //////////////////////////////////////////////////

//! \brief Create the graphic library instance.
//! \return  pointer to graphic library handle.
T_GL_HGRAPHIC_LIB EMV_UI_GoalHandle(void)
{
	if (__EMV_UI_goalHandle == NULL)
	{
		__EMV_UI_goalHandle = GL_GraphicLib_Create();
	}

	return __EMV_UI_goalHandle;
}

//! \brief Destroy the graphic library instance.
void EMV_UI_GoalDestroy(void)
{
	if (__EMV_UI_goalHandle != NULL) {
		GL_GraphicLib_Destroy(__EMV_UI_goalHandle);
		__EMV_UI_goalHandle = NULL;
	}
}

//! \brief Open the GOAL interface (open drivers ...).
void EMV_UI_GoalOpen(void)
{
	if (__EMV_UI_displayDriver == NULL)
		__EMV_UI_displayDriver = Telium_Fopen("DISPLAY", "w*");
	if (__EMV_UI_keyboardDriver == NULL)
		__EMV_UI_keyboardDriver = Telium_Fopen("KEYBOARD", "r*");
	if (__EMV_UI_touchDriver == NULL)
		__EMV_UI_touchDriver = Telium_Fopen("TSCREEN", "r*");
}

//! \brief Close the GOAL interface (close drivers ...).
void EMV_UI_GoalClose(void)
{
	if (__EMV_UI_displayDriver != NULL)
	{
		Telium_Fclose(__EMV_UI_displayDriver);
		__EMV_UI_displayDriver = NULL;
	}
	if (__EMV_UI_keyboardDriver != NULL)
	{
		Telium_Fclose(__EMV_UI_keyboardDriver);
		__EMV_UI_keyboardDriver = NULL;
	}
	if (__EMV_UI_touchDriver != NULL)
	{
		Telium_Fclose(__EMV_UI_touchDriver);
		__EMV_UI_touchDriver = NULL;
	}
}
void EMV_UI_MessageInsertCard(void) {
	EMV_UI_GoalOpen();
	GL_Dialog_Message(EMV_UI_GoalHandle(), NULL, "Insert, Swipe or\n tap card", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);
	EMV_UI_GoalClose();
}
void EMV_UI_MessageTransactionError(void)
{
	EMV_UI_GoalOpen();
	GL_Dialog_Message(EMV_UI_GoalHandle(), NULL, "Transaction\nerror", GL_ICON_ERROR, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
	EMV_UI_GoalClose();
}

//static void pinEntry( T_GL_HWIDGET label, int pinLength) {
//	const char defaultString[] = "- - - -";
//	char string[64];
//	int index;
//
//	GL_Dialog_Password(hGoal, "Password", "Enter password :","/d/d/d/d/d/d", string, sizeof(string), GL_TIME_MINUTE);
//
//	if (pinLength <= 0) {
//		// No PIN entered => display a default message
//		GL_Widget_SetText(label, defaultString);
////		GL_Dialog_Message(EMV_UI_GoalHandle(), "No Pin", "Please Enter your pin", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);
//	} else {
//
//		// Check PIN length to avoid buffer overflows
//		if (pinLength > (sizeof(string) / 2))
//			pinLength = sizeof(string) / 2;
//
//		// Format a string to have a star '*' and a space ' ' for each digit
//		// Ex: for a 4 digits PIN, the string will be "* * * *"
//		for(index = 0; index < pinLength; index++) {
//			string[2 * index] = '*';
//			string[(2 * index) + 1] = ' ';
//		}
//		string[(2 * (pinLength - 1)) + 1] = '\0';
//
//		// Display the string that contains the stars
//		GL_Widget_SetText(label, string);
//	}
//}
