/*
. * jezgro.cpp
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */

#include "jezgro.h"
#include "thread.h"
#include <iostream.h>

PCB* Jezgro::running=0;
PCB* Jezgro::zaludna=0;
int Jezgro::brojac=0;
int Jezgro::test=0;
Lista* Jezgro::sleeplista=0;
NitPom* Jezgro::zaludnaNit=0;
volatile int zahtevana_promena_konteksta = 0;
//volatile unsigned int Jezgro::lockFlag = 1;
unsigned psp;
unsigned pss;
unsigned pbp;
void tick();
InterruptO Jezgro::Stara=0;



void Jezgro::uspavaj(PCB *myPCB){
	Elem* tek=sleeplista->prvi;

	while(tek && myPCB->sleepTime>=tek->pcb->sleepTime){				//dok ne dodjemo do kraja sleepliste ili elementa sa vecim timeRemaining

		myPCB->sleepTime-=tek->pcb->sleepTime;
		tek=tek->sled;
	}


	if(!tek) sleeplista->dodajElem(myPCB);
	else {
		Elem *temp=new Elem(myPCB);						//dodajemo nas element pre pokazivaca tek
		if(tek->pret)temp->pret=tek->pret;
		else sleeplista->prvi=temp;
		tek->pret=temp;
		temp->sled=tek;
		temp->pret->sled=temp;

		tek->pcb->sleepTime-=myPCB->sleepTime;						//smanjivanje timeRemaining
	}
}

void Jezgro::probudi(){
	if(sleeplista && sleeplista->prvi){
		if(sleeplista->prvi->pcb->sleepTime>0)sleeplista->prvi->pcb->sleepTime--;			//oduzimamo prvi element sleep liste

		while(sleeplista->prvi && sleeplista->prvi->pcb->sleepTime==0){					//da li je prvi element dosao do 0 i da li postoji

			Elem* tek=sleeplista->prvi;

			tek->pcb->status=Spreman;
			tek->pcb->sleepTime=0;							//oslobadjanje niti i stavljanje u Scheduler
			Scheduler::put(tek->pcb);


			if(sleeplista->prvi->sled){
				sleeplista->prvi=sleeplista->prvi->sled;		//brisanje prve i prebacivanje na drugu ako druga postoji
				sleeplista->prvi->pret=0;
			}
			else sleeplista->prvi=sleeplista->posl=0;			//ako ne onda stavljamo prvi i posl na 0

		}
	}
}


void Jezgro::inic(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	Jezgro::sleeplista=new Lista();
	Jezgro::running=new PCB(0,0,0);

	Jezgro::zaludnaNit=new NitPom();
	Jezgro::zaludna=zaludnaNit->myPCB;		//POVEZALI zaludna PCB i zaludna NIT u konstruktoru PCBa
	Jezgro::zaludnaNit->start();

		 Jezgro::Stara=getvect(0x08);
		 setvect(0x08,Jezgro::timer);
	UNLOCK
	#endif
}




void Jezgro::restore(){
	#ifndef BCC_BLOCK_IGNORE
	LOCK
		 setvect(0x08,Jezgro::Stara);

	delete Jezgro::zaludna->myThread;
	delete Jezgro::zaludna;
	delete Jezgro::sleeplista;
	delete Jezgro::running;
	UNLOCK
	#endif
}






void interrupt Jezgro::timer(...){

	if (!zahtevana_promena_konteksta){

		Jezgro::Stara();
		probudi();
		tick();

		if (running->timeSlice != 0) {
				if (brojac>0)
					brojac--;												//ako nije nasilno pozvana promena konteksta umanjujemo brojac(timeSlice) niti koji smo ubacili pri pravljenju niti
		}

	}
	if ((brojac == 0 && running->timeSlice != 0) || zahtevana_promena_konteksta) {				//ako je brojac =0 tj ako nema vise dozvoljenog vremena za izvrsavanje ili ako je nasilno pozvana promena konteksta

		#ifndef BCC_BLOCK_IGNORE
		asm {
			mov psp, sp											//prepisujemo sp,ss,bp sa steka i upisuje u pomocne promenjljive
			mov pss, ss
			mov pbp, bp
		}
		#endif

		running->sp = psp;										//cuvamo te vrednosti u pcbu niti koju napustamo
		running->ss = pss;
		running->bp = pbp;


		if(running->status==Spreman && running!=Jezgro::zaludna) {
			Scheduler::put(running);							//ako je nit spremna stavi u Scheduler
		}
		running=Scheduler::get();								//uzmi novu nit

		if(running==0)	{										//ako nema slobodne niti uzmi zaludnu



			running=zaludna;

		}
		psp = running->sp;										//uzimamo kontekst nove niti i prebacujemo u pomocne promenjljive
		pss = running->ss;
		pbp = running->bp;

		if(running!=zaludna) brojac = running->timeSlice;								//ubacujemo vreme trajanja nove niti u brojac
		else brojac=0;																	//ako je zaludna onda je time=0 da bi vreme bilo neograniceno


		#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, psp
			mov ss, pss
			mov bp, pbp;
		}
		#endif

		zahtevana_promena_konteksta=0;					//resetujemo bit za nasilno pozivanje
	}
}

/* 1) Cuvanje konteksta
 * 2) if(status=Spremna) Scheduler::put
 * 3) Scheduler::get
 * 4) ss,sp,bp -> pss,psp,pbp preko asm mov
 * 5) Jezgro::brojac=running->timeSlice
 * 6) if(!zahtevana_promena_konteksta) asm int 60h;
 *
 * Ostali poslovi iz SLEEP fije  ***probudi fija**
 *
 * SREDITI ZALUDNU NIT {
 * 		telo niti= while(1)
 * 		if Scheduler vrati 0 prebacimo running na zaludnu nit
 * 		Nikako stavljati u Scheduler!!!
 * }
 */
