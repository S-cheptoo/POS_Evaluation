#include "sdk_tplus.h"

#include "GL_CommonTypes.h"
#include "GL_Types.h"
#include "GL_Widget.h"
#include "UserInterface.h"
#include "Sale.h"
#include "Menu.h"
#include "CardSwipe.h"


static const char szDate[]= "Date:%.2s/%.2s/%.2s %.2s:%.2s\n";

void enterAmount(void){
	char amountString[100] = "";
	char tcCurr[4+1] = "KSh.";
	double amount;
	char pin[8];
	char mask[64] = "/d/d/d/d";
	char cardInfo[50];
//	ulong ulRet;

	extern T_GL_HGRAPHIC_LIB gGoalGraphicLibInstance;

		// Open an amount input box
		// ************************
		 GL_Dialog_Amount(gGoalGraphicLibInstance, "Sale", "Enter amount :", "/d/d/d,/d/d/d,/d/d/D./D/D", amountString, sizeof(amountString), tcCurr, GL_ALIGN_LEFT, GL_TIME_MINUTE);
		amount= atof(amountString);
		if ((amount<1) || (amount>5000)){ // Shows the amount
			GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Enter a valid amount!!", GL_ICON_INFORMATION, GL_BUTTON_NONE, 4 * GL_TIME_SECOND);
		}
		else{
			processCard(cardInfo);

//			swipeCard();

//			GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please insert/swipe card!", GL_ICON_INFORMATION, GL_BUTTON_VALID_CANCEL, 5*GL_TIME_SECOND);

//
//			Telium_Date_t date;
//			Telium_File_t *hPrinter;
//
//			hPrinter = Telium_Fopen("PRINTER", "w-*"); // Open printer driver
//			if (hPrinter != NULL)
//				{
//			//Telium_Pprintf("\x1b""E%s\n""\x1b""F", ); // Print application name
//			Telium_Pprintf(" Transaction Success !! \n"
//						      "Made by Sandra on\n\n"
//						        );
//			Telium_Read_date(&date); // Print date and time
//			Telium_Pprintf(szDate, date.day, date.month, date.year, date.hour, date.minute);
//			Telium_Pprintf("Amount Paid : %s\n", amountString); // Print amount
//			Telium_Ttestall(PRINTER, 0);
//
//			Telium_Fclose(hPrinter); // Close printer driver
//			}

			// Open a password input box
				// *************************
				GL_Dialog_Password(gGoalGraphicLibInstance, "PIN", "Enter pin:",mask, pin, sizeof(pin), GL_TIME_MINUTE);
//				if ( GL_KEY_ISO_VALID && GL_RESULT_SUCCESS ) // Shows the password

					if (pin[0] != 0){
						GL_Dialog_Message(gGoalGraphicLibInstance, "Sale", "Transaction Successful!", GL_ICON_INFORMATION, GL_BUTTON_VALID_CANCEL, 2*GL_TIME_SECOND);

						Telium_Date_t date;
						Telium_File_t *hPrinter;

						hPrinter = Telium_Fopen("PRINTER", "w-*"); // Open printer driver
						if (hPrinter != NULL)
							{
						//Telium_Pprintf("\x1b""E%s\n""\x1b""F", ); // Print application name
						Telium_Pprintf("Transaction Success !!\n"
								  "Made by Sandra on:\n\n");
						Telium_Read_date(&date); // Print date and time

						Telium_Pprintf(szDate, date.day, date.month, date.year, date.hour, date.minute);
						Telium_Pprintf("===========\n\n");
						Telium_Pprintf("Amount Paid : %s\n", amountString); // Print amount
						Telium_Pprintf("Card Details : %s\n", cardInfo);
						Telium_Ttestall(PRINTER, 0);

						Telium_Fclose(hPrinter); // Close printer driver
							}
					}
				else{
						GL_Dialog_Message(gGoalGraphicLibInstance, "PIN", "Re-enter pin!!", GL_ICON_INFORMATION, GL_BUTTON_VALID_CANCEL, 5*GL_TIME_SECOND);
								EMV_UI_GoalClose();
					}
		}
}
