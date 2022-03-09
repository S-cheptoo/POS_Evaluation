/**
 * Menu.h
 *
 * Header for the Menu source file.
 *
 */
#ifndef __MENU_H
#define __MENU_H

#include <GL_GraphicLib.h>

/*+************* #DEFINES **************************************************+*/

/*+************* CONSTANTS *************************************************+*/

/*+************* STRUCTURES ************************************************+*/

/*+************* VARIABLES *************************************************+*/
extern T_GL_HGRAPHIC_LIB gGoalGraphicLibInstance;

/*+************* FUNCTION PROTOTYPES ***************************************+*/
extern void menuGoalDisplay(void);
extern void initUIContext(int);
extern void releaseUIContext(void);

#endif //__MENU_H
