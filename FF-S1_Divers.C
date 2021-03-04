/******************************************************************************
; 	FILE NAME  	: TP4_Lib_Divers.C
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions diverses mises à disposition
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
// Software_Delay -- Temporisation paramétrable
//      Pour SYSCLK = 2 MHz
//      Vérifiée en  simulation
//      L'argument passé en exprimé en centièmes de seconde (dans l'hypothèse 
//      où SYSCLK = 2MHz)
	 
