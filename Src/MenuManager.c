#include "sdk_tplus.h"

#include "GL_CommonTypes.h"
#include "GL_Types.h"
#include "GL_Widget.h"

//extern T_GL_HGRAPHIC_LIB hGoal;

static const char szDate[]= "Date:%.2s/%.2s/%.2s %.2s:%.2s\n";

void enterBillPayment(void)
{
	extern T_GL_HGRAPHIC_LIB gGoalGraphicLibInstance;

	// Local variables
	// ***************
	char billNo[100] = "";
	char billAmount[100]="";
	ulong ulRet;
	ulong Ret;

	// Open a text input box
	// *********************
	ulRet = GL_Dialog_Text(gGoalGraphicLibInstance, "Bill Payment", "Enter bill number# :","/d/d/d/d/d/d/d/d/D", billNo, sizeof(billNo), GL_TIME_MINUTE);
	if (strlen(billNo)<= 8 && strlen(billNo)>=5) // Shows the bill number
	{
		Ret = GL_Dialog_Text(gGoalGraphicLibInstance, "Bill Payment", "Enter bill amount :","/d/d/d,/d/d/D./D/D", billAmount, sizeof(billAmount), GL_TIME_MINUTE);
		if(Ret==GL_RESULT_SUCCESS);
			  Telium_Date_t date;
			    Telium_File_t *hPrinter;

			    // Print application info
//			    ObjectGetInfo(OBJECT_TYPE_APPLI, no, &infos); // Retrieve application info

			    hPrinter = Telium_Fopen("PRINTER", "w-*"); // Open printer driver
			    if (hPrinter != NULL)
			    {
//			        Telium_Pprintf("\x1b""E%s\n""\x1b""F", ); // Print application name
			        Telium_Pprintf("Bill Payment Receipt \n"
			                        "Served by Sandra\n"
			                		"========================\n");
			        Telium_Read_date(&date); // Print date and time
			        Telium_Pprintf(szDate, date.day, date.month, date.year, date.hour, date.minute);
			        Telium_Pprintf("Bill Number    : %s\n", billNo);
			        Telium_Pprintf("Bill Amount     : %s\n", billAmount);
			        Telium_Ttestall(PRINTER, 0);

			        Telium_Fclose(hPrinter); // Close printer driver
			    }
			    if (GL_KEY_UTF8_VALID || GL_KEY_NONE || GL_KEY_UTF8_CANCEL ){
			    	EMV_UI_GoalClose();

			    }

	}
	else
	{
		GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Enter a valid bill number", GL_ICON_INFORMATION, GL_BUTTON_NONE, 4 * GL_TIME_SECOND);
	}
}





