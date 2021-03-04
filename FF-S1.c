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

sbit FREQ_OUT = P3^2;
sbit CHG_FREQ = P2^2;
sbit LED = P1^6;
sbit BOUTON = P3^7;
int i=1;

#define Reset_Timer3Overflow TMR3CN &= 0x04
#define Disable_Timer3 TMR3CN = 0x00
#define Reset_Timer2External EXF2 = 0
// Prototypes de Fonctions

//MODE DE FONCTIONNEMENT
// On utilise timer3 comme générateur de signaux parce qu'il ne peut faire que l'auto rechargement 16bits, ce qui est uniquement utile pour ce cas de figure
// On est obligé de faire ça car sinon il ne restera plus assez de timers pour la capture(tâche1) et le baud-rate generator(tâche2)
// On utilise timer 2 en mode capture pour gérer le changement de fréquence
//Le changement se fait dans son ISR. Il y a beaucoup de ports à allouer et de crossbar à écrire, et il y a pas moyen de vérifier sans carte devant soi :/





void Phase_Usage(void){
	if (BOUTON == 1){ //A refaire avec des flags
		//Disable_Timer3;
	}
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
		  TMR3RL = 0xD8EF;  //10kHz à 0xFF98 1kHz à 0xFFCE 100Hz à 0xFE0B
	    TMR3CN = 0x04; //Timer 3 est enabled
	    T2CON = 0xF; //Timer 2 actif en auto-reload, en mode compteur, avec captures autorisées
	// Fin Code phase Démarrage	***************************************************
	
	
	while(1)
        {
					Phase_Usage();
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
	FREQ_OUT = !FREQ_OUT;
	Reset_Timer3Overflow;
}

void ISR_timer2External() interrupt 5
{
	Reset_Timer2External;
	if (i==0){
		i=i+1;
		TMR3RL = 0xD8EF; //100Hz
	}
	if (i==1){
		i=i+1;
		TMR3RL = 0xFC17; //1kHz
	}
	if (i==2){
		TMR3RL = 0xFF98; //10kHz
		i=0;
	}
	
}