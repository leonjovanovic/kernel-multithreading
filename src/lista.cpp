/*
 * lista.cpp
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */

#include "lista.h"


void Lista::dodajElem(PCB* pcb){
//	#ifndef BCC_BLOCK_IGNORE
//	LOCK
	if(!prvi) prvi=posl=new Elem(pcb);
	else {
		Elem *tek=posl;
		posl->sled=new Elem(pcb);
		posl=posl->sled;
		posl->pret=tek;
		posl->sled=0;
	}
//	UNLOCK
//	#endif
}

void Lista::dodajSleepElem(PCB *pcb, Elem *tek){		//ubacivanje u listu gde je pcb novi element a tek pokazivac na element ispred elementa koji hocemo da ubacimo
//	#ifndef BCC_BLOCK_IGNORE
//	LOCK
	Elem *temp=new Elem(pcb);
	temp->pret=tek->pret;
	tek->pret=temp;
	temp->sled=tek;
	temp->pret->sled=temp;
//	UNLOCK
//	#endif
}

PCB* Lista::uzmiElem(){
//	#ifndef BCC_BLOCK_IGNORE
//	LOCK
	if(this->prvi==0){
		//UNLOCK
		return 0;
	}
	Elem* temp=prvi;
	PCB* pcb=temp->pcb;
	prvi=prvi->sled;
	temp->sled=0;
	prvi->pret=0;
	delete temp;
	if(prvi==0)posl=0;
//	UNLOCK
	return pcb;
//	#endif
}

/*void Lista::izbrisiElem(PCB *pcb){				//NE ZNAM DA LI JE TACNO, NISAM KORISTIO *********PAZLJIVO KORISTITI*************
	Elem* tek=prvi;
	while(tek->pcb!=pcb)tek=tek->sled;
	if(tek){
		if(tek->sled) {
			if(tek==prvi) prvi=tek->sled;
			else if(tek==posl)posl=tek->pret;
				 else tek->pret->sled=tek->sled;
		}
		else prvi=posl=0;
		tek->sled=tek->pret=0;
	}
}*/

Lista::~Lista(){
	//#ifndef BCC_BLOCK_IGNORE
//	LOCK
	while(prvi){
		Elem* sledeci=prvi->sled;
		delete prvi;
		prvi=sledeci;
	}
//	UNLOCK
//	#endif
}
