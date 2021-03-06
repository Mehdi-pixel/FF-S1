/******************************************************************************
; 	FILE NAME  	: TP4_Lib_Divers.C
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions diverses mises � disposition
;
; 	REVISION 1.0
;   Ce fichier contient diverses fonctions susceptibles de vous faire gagner 
;   un peu de temps
*/
//******************************************************************************

#include "C8051F020.h"
#include "c8051F020_SFR16.h"
#include "FF-S1_Divers.h"

//*****************************************************************************	 
//*****************************************************************************	 

//*****************************************************************************	 
//*****************************************************************************	 
// Software_Delay -- Temporisation param�trable
//      Pour SYSCLK = 2 MHz
//      V�rifi�e en  simulation
//      L'argument pass� en exprim� en centi�mes de seconde (dans l'hypoth�se 
//      o� SYSCLK = 2MHz)
	 
