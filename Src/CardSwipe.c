#include <sdk_tplus.h>
#include "CardSwipe.h"
#include "string.h"
#include "GL_CommonTypes.h"
#include "GL_Types.h"
#include "GL_Widget.h"
#include "GL_Dialog.h"
#include "GL_GraphicLib.h"

//void IsoError(int iSta, char *pcTrk)
//{
//	switch (iSta)
//	{
//		case DEF_SEP: strcpy(pcTrk, "Separator fault");  break;
//		case DEF_PAR: strcpy(pcTrk, "Parity fault");     break;
//		case DEF_LRC: strcpy(pcTrk, "LRC fault");        break;
//		case DEF_LUH: strcpy(pcTrk, "Luhn fault");       break;
//		case DEF_NUM: strcpy(pcTrk, "Numerical fault");  break;
//		case NO_DATA: strcpy(pcTrk, "No readable data"); break;
//		default:      strcpy(pcTrk, "Unknown error");    break;
//	}
//}

T_GL_HGRAPHIC_LIB gGoalGraphicLibInstance;

int checkISO(int iRet){

	T_GL_HGRAPHIC_LIB gGoalGraphicLibInstance;

	char err[20];

	memset(err, 0, sizeof(err));

	if (iRet == ISO_OK) {

		return TRUE;

	} else {

		switch (iRet)
		{
			case DEF_SEP: strcpy(err, "Separator fault");  break;
			case DEF_PAR: strcpy(err, "Parity fault");     break;
			case DEF_LRC: strcpy(err, "LRC fault");        break;
			case DEF_LUH: strcpy(err, "Luhn fault");       break;
			case DEF_NUM: strcpy(err, "Numerical fault");  break;
			case NO_DATA: strcpy(err, "No readable data"); break;
			default:      strcpy(err, "Unknown error");    break;
		}

		GL_Dialog_Message(gGoalGraphicLibInstance, "Swiping Error!!", err , GL_ICON_ERROR, GL_BUTTON_VALID_CANCEL, 2*1000);
		return FALSE;
	}

}

void swipeOrCard(char * message){
	GL_Dialog_Message(gGoalGraphicLibInstance, "Card", message , GL_ICON_INFORMATION, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
}


//	// Open peripherals
//	// ================
//	if (IsISO1() == 1)
//	{
//		hMag31 = Telium_Fopen("SWIPE31", "r*");       // Open mag1 peripheral
//		CHECK(hMag31, lblKO);
//	}
//    if (IsISO2() == 1)
//    {
//    	hMag2 = Telium_Fopen("SWIPE2", "r*");         // Open mag2 peripheral
//    	CHECK(hMag2, lblKO);
//    }
//    if (IsISO3() == 1)
//    {
//    	hMag3 = Telium_Fopen("SWIPE3", "r*");         // Open mag3 peripheral
//    	CHECK(hMag3, lblKO);
//    }


 void processCard(char *cardInfo){

	 T_GL_HGRAPHIC_LIB gGoalGraphicLibInstance;

	 char tcTmp[128];
	 char *pcSrc, *pcDst;
	 char tcTrk1[128], tcTrk2[128], tcTrk3[128];
	 Telium_File_t * hCam = NULL;
	 Telium_File_t *hMag31=NULL, *hMag2=NULL, *hMag3=NULL;
	 int check;
	 byte ucLen=0;
     int ret, event, cardPresent;
    unsigned char ucStatus;


    	//Initialization
    	cardPresent = FALSE;
    	strcpy(tcTrk1, "No readable data");
    	strcpy(tcTrk2, "No readable data");
    	strcpy(tcTrk3, "No readable data");


    	while(!cardPresent) {

    		GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please Insert or Swipe Card", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);


    		// Open peripherals

    		//Check MagStripe
    		if (IsISO1() == 1) {
    			//Open MagStripe
    			hMag31 = Telium_Fopen("SWIPE31", "r*");
    		}

    		if (IsISO2() == 1) {
    			//Open MagStripe
    			hMag2 = Telium_Fopen("SWIPE2", "r*");
    		}

    		if (IsISO3() == 1) {
    			//Open MagStripe
    			hMag3 = Telium_Fopen("SWIPE3", "r*");
    		}


    		//Open CAM
    		hCam = Telium_Fopen("CAM0", "rw");


    		//Wait for swipe event
    		event = Telium_Ttestall(CAM0 | SWIPE31 | SWIPE2 | SWIPE3, 0);

    		//Retrieve and Analyze ISO1
    		if (event & SWIPE31) {

    			//Show event
    			swipeOrCard("Swipe 31");

    			memset(tcTmp, 0, sizeof(tcTmp));
    			memset(tcTrk1, 0, sizeof(tcTrk1));

    			ret = Telium_Is_iso1(hMag31, &ucLen, (byte*)tcTmp);
    			check = checkISO(ret);

    			if (check == TRUE) {

    				cardPresent = TRUE;

    				pcSrc = tcTmp;
    				pcDst = tcTrk1;

    				while(*pcSrc) {
    					if(*pcSrc++ == '%')
    						break;
    				}

    				// Copy all data between start and end sentinels
    				while(*pcSrc) {
    					if(*pcSrc == '?')
    						break;
    					*pcDst++ = *pcSrc++;
    				}

    				GL_Dialog_Message(gGoalGraphicLibInstance, "Card Details", tcTrk1 , GL_ICON_INFORMATION, GL_BUTTON_NONE, 8*1000);

    				strcpy(cardInfo, tcTrk1);
    				//return tcTrk1;

    			}
    		}

    		if (event & SWIPE2) {

    			//Show event
    			swipeOrCard("Swipe 2");

    			memset(tcTmp, 0, sizeof(tcTmp));
    			memset(tcTrk2, 0, sizeof(tcTrk2));
    			ret = Telium_Is_iso2(hMag2, &ucLen, (byte*)tcTmp);
    			check = checkISO(ret);

    			if (check == TRUE) {

    				cardPresent = TRUE;

    				pcSrc = tcTmp;
    				pcDst = tcTrk2;

    				while(*pcSrc) {                                  // Find start sentinel
    					if(*pcSrc++ == 'B')
    						break;
    				}
    				while(*pcSrc) {                                  // Copy all data between start and end sentinels
    					if(*pcSrc == 'F')
    						break;
    					if(*pcSrc == 'D')

    						//Truncate Data to return Card Number only
    						//*pcSrc = '=';
    						break;

    						*pcDst++ = *pcSrc++;
    				}

    				GL_Dialog_Message(gGoalGraphicLibInstance, "Card Details", tcTrk2 , GL_ICON_INFORMATION, GL_BUTTON_NONE, 8*1000);


    				strcpy(cardInfo, tcTrk2);
    				//return tcTrk2;

    			}

    		}

    		if (event & SWIPE3) {


    			//Show event
    			swipeOrCard("Swipe 3");

    			memset(tcTmp, 0, sizeof(tcTmp));
    			memset(tcTrk3, 0, sizeof(tcTrk3));

    			ret = Telium_Is_iso3(hMag3, &ucLen, (byte*)tcTmp);
    			check = checkISO(ret);


    			if (check == TRUE) {

    				cardPresent = TRUE;

    				pcSrc = tcTmp;
    				pcDst = tcTrk3;

    				while(*pcSrc) {
    					if(*pcSrc++ == 'B')
    						break;
    				}

    				while(*pcSrc) {
    					if(*pcSrc == 'F')
    						break;
    					if(*pcSrc == 'D')
    						*pcSrc = '=';
    						*pcDst++ = *pcSrc++;
    				}

    				GL_Dialog_Message(gGoalGraphicLibInstance, "Card Information", tcTrk3 , GL_ICON_INFORMATION, GL_BUTTON_NONE, 8*1000);


    				strcpy(cardInfo, tcTrk3);
    				//return tcTrk3;

    			}
    		}

    		//Analyze and retrieve CAM
    		if (event & CAM0) {

    			//Show event
    			swipeOrCard("Card Inserted");

    			Telium_Status(hCam, &ucStatus);
    			if ((ucStatus & CAM_PRESENT) != 0) {
    					// A card is present
    					cardPresent = TRUE;
    			} else {

    				cardPresent = FALSE;
    			}

    		}


    		Telium_Fclose(hMag31);
    		Telium_Fclose(hMag2);
    		Telium_Fclose(hMag3);
    		Telium_Fclose(hCam);
    	}

    }




