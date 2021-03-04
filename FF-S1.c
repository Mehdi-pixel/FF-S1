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

unsigned char Intensite=0xA; //On met � 10% comme valeur d'exemple
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
	if (Lum_Nbre !=0){ //Mode de clignotement (non fini)
		if (Lum_ON !=0){
			//On garde allum� pendant Lum_ON millisecondes
			//On ne peut PAS utiliser de while car �a bloque le processeur
		}
		if (Lum_OFF !=0){
			//On garde �teint pendant Lum_ON millisecondes
			//On ne peut PAS utiliser de while car �a bloque le processeur
		}
		Lum_Nbre = Lum_Nbre - 1;
	}
	//Gestion du rapport cyclique
	if(FREQ_OUT) {
		TMR3RL = 0xF4EF; // A terme, on veut pouvoir influencer ces valeurs de reload avec Intensite
	}
	else {
		TMR3RL = 0xFFFF; // On garde � 65535 pour avoir la plage la plus grande possible entre les deux reload
	}
	//G�n�rateur de signaux
	FREQ_OUT = !FREQ_OUT;
	Reset_Timer3Overflow;
}

void Lumiere_Stop(void){
	//If (R�ception du caract�re d'extinction par l'UART) {
	Disable_Timer3; //D�sactive le signal d'allumage du pointeur
	//}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
       
	  Init_Device();  // Appel des configurations globales
	  
// D�but Insertion Code Configuration des p�riph�riques ***********************
 
	
// Fin Code Initialisations ***************************************************

	
// D�but Insertion Code Phase D�marrage ***************************************	
			EA = 1;
	// Fin Code phase D�marrage	***************************************************
	
	
	while(1)
        {
			Lumiere_Stop() //On v�rifie en permanence si on re�oit le caract�re d'extinction
        }				               	
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fonctions de configuration des divers p�riph�riques
//-----------------------------------------------------------------------------
// Ins�rez vos fonctions de configuration ici

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fonctions d'interruptions
//-----------------------------------------------------------------------------
// Ins�rez vos fonctions d'interruption ici

void ISR_timer3Overflow() interrupt 14
{
Lumiere(Intensite,Lum_ON, Lum_OFF, Lum_Nbre)
}