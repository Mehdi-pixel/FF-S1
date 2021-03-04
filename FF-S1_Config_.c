/******************************************************************************
; 	FILE NAME  	: TP4_Lib_Config_Globale_8051F020.C
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Configurations GLOBALES pour le 8051F020
;
; 	REVISION 1.0
;   Ce fichier contient les codes de configuration globale du 8051F020
;     - Configuration de l'horloge système SYSCLK
;     - Configuration des broches du 80851F020
;     - Configuration Reset et watchdog
*/
//******************************************************************************

#include "C8051F020.h"
#include "c8051F020_SFR16.h"

sbit FREQ_OUT = P3^2;
sbit CHG_FREQ = P2^2;
sbit LED = P1^6;

// Peripheral specific initialization functions,
// Called from the Init_Device() function

//-----------------------------------------------------------------------------
// Dévalidation du watchdog
//-----------------------------------------------------------------------------
void Reset_Sources_Init()
{
	 WDTCN = 0xDE;
	 WDTCN = 0XAD;
// Début Insertion Code configuration Reset  **********************************
	 EA = 0;
	 EIE2 = 0x01; //Timer 3 interrupt enabled
	 ET2 = 1; //Timer 2 interrupt enabled
	 EA = 1;
// Fin Insertion Code configuration Reset et **********************************
}

//-----------------------------------------------------------------------------
// Configuration des Ports d'entrée-sorties
//-----------------------------------------------------------------------------

void Port_IO_Init()
{
    // P0.0  -  Unassigned, Open-Drain, Digital
    // P0.1  -  Unassigned, Open-Drain, Digital
    // P0.2  -  Unassigned, Open-Drain, Digital
    // P0.3  -  Unassigned,  Open-Drain, Digital
    // P0.4  -  Unassigned,  Open-Drain, Digital
    // P0.5  -  Unassigned,  Open-Drain, Digital
    // P0.6  -  Unassigned,  Open-Drain, Digital
    // P0.7  -  Unassigned,  Open-Drain, Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  LED       ,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  Unassigned,  Open-Drain, Digital
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  CHG_FREQ,    Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  FREQ_OUT,    Push-Pull, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Open-Drain, Digital
    // P3.5  -  Unassigned,  Open-Drain, Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital Input INT6
    // P3.7  -  BP        ,  Open-Drain, Digital Input INT7
		
		// P4.0 to P7.7   Unassigned,  Open-Drain, Digital
		
// Début Insertion Code configuration Crossbar et GPIO ************************
//On a P2.2 en entrée / P1.6 et P3.2 en sortie
		P0MDOUT   |= 0x01; // P0.0 en Push-Pull        Assigné par le prof dans TP4, je veux pas casser le programme
    P1MDOUT   |= 0x44; // P1.6 et P1.2 en Push-Pull  Celui là aussi, mais ça fait plus sens car P1.6 est en sortie car LED
		//P2MDOUT   |=0x0; Inchangé, on laisse en Open Drain car entrée
		P3MDOUT   |= 0x04; //P3.2 en Push-Pull, car c'est une sortie
    XBR0      = 0x04; //Activation de l'UART0
    XBR1      = 0xFE; //Activation de l'external input Timer2 et du sysclock (le reste jsp mais je veux pas casser le programme)
    XBR2      = 0x58; //Activation de beaucoup de trucs, wow wtf
		
		
     
// Fin Insertion Code configuration Crossbar et GPIO **************************

}

//-----------------------------------------------------------------------------
// Config oscillateur - SYSCLK = 22,1184MHz - Oscillateur externe à quartz 
//-----------------------------------------------------------------------------
void Oscillator_Init_Osc_Quartz()
{

	  int i = 0;
    OSCXCN    = 0x67;  // Config de l'horloge externe - Quartz > 6,7 MHz
    for (i = 0; i < 3000; i++);  // attente stabilisation Fosc quartz
    while ((OSCXCN & 0x80) == 0); // validation stabilité du quartz
    OSCICN    = 0x0C;  // Commutation sur oscillateur externe 
	                     // L'oscillateur n'est pas stopp
}

//-----------------------------------------------------------------------------
// Initialisation globale du Microcontrôleur - 
//-----------------------------------------------------------------------------
void Init_Device(void)
{
    Reset_Sources_Init();
    Port_IO_Init();
    Oscillator_Init_Osc_Quartz();
}



