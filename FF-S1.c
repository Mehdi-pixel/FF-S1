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
#include "FF-S1_Config.h"
#include "FF-S1_Divers.h"

unsigned char Intensite=0xA; //On met � 10% comme valeur d'exemple
unsigned char Lum_ON=0;
unsigned char Lum_OFF=0;
unsigned char Lum_Nbre=0;
int one_mil = 0x820; // C'est le nombre de cycles processeur correspondant � 1ms

sbit FREQ_OUT = P3^2;
sbit CHG_FREQ = P0^2;
sbit LED = P1^6;
sbit BOUTON = P3^7;
int i=1;

#define Reset_Timer3Overflow TMR3CN &= 0x04
#define Disable_Timer3 TMR3CN = 0x00
// Prototypes de Fonctions


void Lumiere(unsigned char Intensite,unsigned char Lum_ON,unsigned char Lum_OFF,unsigned char Lum_Nbre){
	if (Lum_Nbre !=0 && Lum_ON !=0){
		//On garde allum� (� l'intensit� qu'on veut) pendant Lum_ON millisecondes
		TMR3RL = (0xFFFF-(one_mil*Lum_ON));
		if(FREQ_OUT) {
			TMR3RL = 0xE018; //Normalement variable avec Intensite
		}
		else {
			TMR3RL = 0xF7DF; // On ne garde PAS � 65535, �a cause des erreurs
		}
		Lum_Nbre = Lum_Nbre - 1;
	}
			
		if (Lum_Nbre !=0 && Lum_OFF !=0){
			//On garde �teint pendant Lum_OFF millisecondes => On met FREQ_OUT � 0 et on ne rentre plus dans l'ISR pendant Lum_OFF secondes
			FREQ_OUT = 0;
			TMR3RL = (0xFFFF-(one_mil*Lum_OFF));
			Lum_Nbre = Lum_Nbre - 1;
		}
		else {
	//Gestion du rapport cyclique
	if(FREQ_OUT) {
		TMR3RL = 0xE018; // A terme, on veut pouvoir influencer ces valeurs de reload avec Intensite
	}
	else {
		TMR3RL = 0xF7DF; // On ne garde PAS � 65535, �a cause des erreurs
	}
	//G�n�rateur de signaux
	FREQ_OUT = !FREQ_OUT;
}
	Reset_Timer3Overflow;
}

void Lumiere_Stop(void){
	//If (R�ception du caract�re d'extinction par l'UART) {
	//Disable_Timer3;		//D�sactive le signal d'allumage du pointeur
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
			Lumiere_Stop(); //On v�rifie en permanence si on re�oit le caract�re d'extinction
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
Lumiere(Intensite,Lum_ON, Lum_OFF, Lum_Nbre);
}