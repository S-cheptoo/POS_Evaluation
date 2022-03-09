#ifndef USER_INTERFACE_H_INCLUDED
#define USER_INTERFACE_H_INCLUDED

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

T_GL_HGRAPHIC_LIB EMV_UI_GoalHandle(void);
void EMV_UI_GoalDestroy(void);

void EMV_UI_GoalOpen(void);
void EMV_UI_GoalClose(void);
void EMV_UI_MessageInsertCard(void);
void EMV_UI_MessageTransactionError(void);
int ComputeTotalAmount(void);
//static void pinEntry(struct EPSTOOL_PinEntry_Infos_t *interface, T_GL_HWIDGET label, int pinLength);

#endif
