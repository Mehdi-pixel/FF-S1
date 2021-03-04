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

unsigned char Intensite=0xA; //On met à 10% comme valeur d'exemple
unsigned char Lum_ON=0;
unsigned char Lum_OFF=0;
unsigned char Lum_Nbre=0;
int one_mil = 0x820; // C'est le nombre de cycles processeur correspondant à 1ms

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
		//On garde allumé (à l'intensité qu'on veut) pendant Lum_ON millisecondes
		TMR3RL = (0xFFFF-(one_mil*Lum_ON));
		if(FREQ_OUT) {
			TMR3RL = 0xE018; //Normalement variable avec Intensite
		}
		else {
			TMR3RL = 0xF7DF; // On ne garde PAS à 65535, ça cause des erreurs
		}
		Lum_Nbre = Lum_Nbre - 1;
	}
			
		if (Lum_Nbre !=0 && Lum_OFF !=0){
			//On garde éteint pendant Lum_OFF millisecondes => On met FREQ_OUT à 0 et on ne rentre plus dans l'ISR pendant Lum_OFF secondes
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
		TMR3RL = 0xF7DF; // On ne garde PAS à 65535, ça cause des erreurs
	}
	//Générateur de signaux
	FREQ_OUT = !FREQ_OUT;
}
	Reset_Timer3Overflow;
}

void Lumiere_Stop(void){
	//If (Réception du caractère d'extinction par l'UART) {
	//Disable_Timer3;		//Désactive le signal d'allumage du pointeur
	//}
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
			Lumiere_Stop(); //On vérifie en permanence si on reçoit le caractère d'extinction
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
Lumiere(Intensite,Lum_ON, Lum_OFF, Lum_Nbre);
}