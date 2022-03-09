#include "sdk_tplus.h"

#include "GL_CommonTypes.h"
#include "GL_Types.h"
#include "GL_Widget.h"
#include "UserInterface.h"
#include "Sale.h"
#include "Menu.h"


static const char szDate[]= "Date:%.2s/%.2s/%.2s %.2s:%.2s\n";

void saleCashBack(void){
	int result=0, ret= 0;
	const char entryMask[] = "/d/d/d,/d/d/d,/d/d/D./D/D";
	char currencyLabel[3 + 1] ;
	char amountString[32 + 1];
	char cashBackAmtString[32 + 1];
	char pin[8];
	char mask[64] = "/d/d/d/d/d/d";
   char totalAmount[30];


	T_GL_HGRAPHIC_LIB hGoal;      // Handle of the graphics object library
	memset(cashBackAmtString, 0, sizeof(cashBackAmtString));
	memset(amountString, 0, sizeof(amountString));
    int cashAmount = atoi(amountString);
    int cashBack= atoi(cashBackAmtString);
     int total= cashAmount + cashBack;
    sprintf(totalAmount ,"%d", total);



	result=GL_Dialog_Amount(hGoal, " ", "Enter Amount:", entryMask, amountString, sizeof(amountString), currencyLabel, GL_ALIGN_RIGHT, 2 * GL_TIME_MINUTE);
	ret=GL_Dialog_Amount(hGoal, " ", "Enter CashBack Amount:", entryMask, cashBackAmtString, sizeof(cashBackAmtString), currencyLabel, GL_ALIGN_RIGHT, 2 * GL_TIME_MINUTE);
	if((result==GL_RESULT_SUCCESS)&&(ret==GL_RESULT_SUCCESS)){
//		computeTotalAmount();
		EMV_UI_MessageInsertCard();
				if(GL_KEY_OK){
//					pinEntry();
					GL_Dialog_Password(hGoal, "Password", "Enter password :",mask, pin, sizeof(pin), GL_TIME_MINUTE);

					Telium_Date_t date;
					Telium_File_t *hPrinter;

					hPrinter = Telium_Fopen("PRINTER", "w-*"); // Open printer driver
					if (hPrinter != NULL)
						{
					//Telium_Pprintf("\x1b""E%s\n""\x1b""F", ); // Print application name
					Telium_Pprintf(" Sale with CashBack !! \n"
								      "Made by Sandra on\n\n"
										"==================="
								        );
					Telium_Read_date(&date); // Print date and time
					Telium_Pprintf(szDate, date.day, date.month, date.year, date.hour, date.minute);
					Telium_Pprintf("Sale Amount  : %s\n", amountString); // Print amount
					Telium_Pprintf("CashBack Amount  : %s\n", cashBackAmtString);
					Telium_Pprintf("Total Amount : %s\n", totalAmount);
//					sscanf(amtTot, "%f", &amtTot);
//					Telium_Pprintf("Total Amount : %f\n", amtTot);
					Telium_Ttestall(PRINTER, 0);

					Telium_Fclose(hPrinter); // Close printer driver
					}
				}
	}else{
		GL_Dialog_Message(hGoal, "Error", "Please re-enter the values", GL_ICON_INFORMATION, GL_BUTTON_VALID_CANCEL, 5*GL_TIME_SECOND);
		EMV_UI_GoalClose();
	}
}
