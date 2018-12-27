/*
 * KernelEv.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#include "KernelEv.h"
//Specijalna nit pravi ker event tj tastere koji postavljaju specijalnu nit kao kreatora i samo on moze da se blokira
KernelEv::KernelEv(IVTNo ivtNo) { //je valjda svaki taster
//	#ifndef BCC_BLOCK_IGNORE
//	LOCK
	if(IVTEntry::ivTable[ivtNo]){
	ulaz=ivtNo;
	kreator=Jezgro::running;
	blokirana=0;
	value=0;

	IVTEntry::ivTable[ulaz]->myEvent=this;
	}
//	UNLOCK
//	#endif
}

KernelEv::~KernelEv() {
//	#ifndef BCC_BLOCK_IGNORE
//	LOCK
	IVTEntry::ivTable[ulaz]->myEvent=0;
//	UNLOCK
//	#endif
}


void KernelEv::wait(){
//	#ifndef BCC_BLOCK_IGNORE
//	LOCK
	if(Jezgro::running==kreator)		//samo nit koja je napravila event moze da se blokira na semaforu
		if(value==0){
			kreator->status=Blokiran;
			blokirana=Jezgro::running;
			dispatch();
		}
		else value=0;

//	UNLOCK
//	#endif
}



void KernelEv::signal(){		//signalizira da se nesto desilo
//	#ifndef BCC_BLOCK_IGNORE
//	LOCK
	if(blokirana==0) value=1;	//ukoliko ne postoji blokirana nit  semafor postavljamo na 1
	else{
		blokirana->status=Spreman;
		if(blokirana!=Jezgro::zaludna)Scheduler::put(blokirana);
		blokirana=0;		//deblokiramo tu nit i stavljamo u Scheduler
	}

//	UNLOCK
//	#endif
}

