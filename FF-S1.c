//-----------------------------------------------------------------------------
// TP5.c
//-----------------------------------------------------------------------------
// AUTH: 
// DATE: 
//
// Target: C8051F02x
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include <C8051F020.h>
#include "c8051F020_SFR16.h"
#include "TP5_Lib_Config_Globale_8051F020.h"
#include "TP5_Lib_Divers.h"

unsigned char Intensite=0xA;
unsigned char Lum_ON;
unsigned char Lum_OFF;
unsigned char Lum_Nbre;

sbit FREQ_OUT = P3^2;
sbit CHG_FREQ = P0^2;
sbit LED = P1^6;
sbit BOUTON = P3^7;
int i=1;

#define Reset_Timer3Overflow TMR3CN &= 0x04
#define Disable_Timer3 TMR3CN = 0x00
// Prototypes de Fonctions




void Lumiere(unsigned char Intensite,unsigned char Lum_ON,unsigned char Lum_OFF,unsigned char Lum_Nbre){

	

}

void Lumiere_Stop(void){
	Disable_Timer3;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
       
	  Init_Device();  // Appel des configurations globales
	  
// Début Insertion Code Configuration des périphériques ***********************
 
	
// Fin Code Initialisations ***************************************************

	
// Début Insertion Code Phase Démarrage ***************************************	
			EA = 1;
	// Fin Code phase Démarrage	***************************************************
	
	
	while(1)
        {
			Lumiere(Intensite,Lum_ON,Lum_OFF,Lum_Nbre);
        }				               	
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fonctions de configuration des divers périphériques
//-----------------------------------------------------------------------------
// Insérez vos fonctions de configuration ici

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fonctions d'interruptions
//-----------------------------------------------------------------------------
// Insérez vos fonctions d'interruption ici

void ISR_timer3Overflow() interrupt 14
{
//Générateur de signaux
if(FREQ_OUT) {
	TMR3RL = 0xF4EF;
}
else {
	TMR3RL = 0xFF17;  
}
FREQ_OUT = !FREQ_OUT;
Reset_Timer3Overflow;
}