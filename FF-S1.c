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

unsigned char Intensite=100; //On met à 20% comme valeur d'exemple
unsigned char Lum_ON=5;
unsigned char Lum_OFF=10;
unsigned char Lum_Nbre=10;
int currentNum = 0;
int one_cs = 20828; //Nombre de cycles processeur pour attendre 1cs.
int cptON = 0;
int cptOFF = 0;
int divTimer = 0;
int t_on = 0;
int t_off = 0;

sbit LED = P1^6;
int i=1;

#define Reset_Timer3Overflow TMR3CN &= 0x04
#define Disable_Timer3 TMR3CN = 0x00
// Prototypes de Fonctions


void Lumiere(unsigned char Intensite,unsigned char Lum_ON,unsigned char Lum_OFF,unsigned char Lum_Nbre){
	//Gestion de l'intensité
	t_on = one_cs*(Intensite/100.0);
	t_off = one_cs - t_on;
		if (currentNum != Lum_Nbre && Lum_ON != 0 && cptON != 20*Lum_ON){
			//On garde allumé (à l'intensité qu'on veut) pendant Lum_ON décisecondes
			cptON++;
			if(LED) {
				TMR3RL = 0xFFFF - t_on; //Variable avec Intensite
		}
			else if (t_off != 0) {
				TMR3RL = 0xFFFF - t_off;
		}
		//Générateur de signaux
		LED = !LED;
		Reset_Timer3Overflow;
		cptOFF = 0; //Reset du compteur de Lum_OFF pour son prochain allumage
		return ;
	}
		else if (currentNum != Lum_Nbre && Lum_OFF != 0 && cptOFF != 20*Lum_OFF){
			//On garde éteint pendant Lum_OFF millisecondes => On met LED à 0 et on ne rentre plus dans l'ISR pendant Lum_OFF secondes
			cptOFF++;
			LED = 0;
			TMR3RL = 0xFFFF - 10414; //On le met à la même période que le ON ((TMRRL dutyON + TMRRL dutyOFF )/ 2)
			Reset_Timer3Overflow;
			if ( cptOFF == 20*Lum_OFF) {
				currentNum++;
				cptON = 0; //Reset du compteur de Lum_ON pour son prochain allumage
			}
			return ; //On sort immédiatement de la fonction
		}
		//Gestion du rapport cyclique : Mode basique sans clignotement
	if(LED) {
		TMR3RL = 0xFFFF - t_on; // A terme, on veut pouvoir influencer ces valeurs de reload avec Intensite
	}
	else {
		TMR3RL = 0xFFF - t_off; // On ne garde PAS à 65535, ça cause des erreurs
	}
	//Générateur de signaux
	LED = !LED;
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