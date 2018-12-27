/*
 * thread.cpp
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */

#include <iostream.h>
#include <dos.h>
#include <stdlib.h>
#include "jezgro.h"
#include "lock.h"


Thread::Thread(StackSize stackSize, Time timeSlice) {
#ifndef BCC_BLOCK_IGNORE
	LOCK
	myPCB=new PCB(stackSize,timeSlice,this);			//pravimo novi PCB
	//cout<<"inicThreada"<<endl;
	UNLOCK
#endif
}



void Thread::start(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	this->myPCB->inicSteka();
	this->myPCB->status=Spreman;
	if(this->myPCB!=Jezgro::zaludna) Scheduler::put(myPCB);
	//cout<<"startThread"<<endl;
	UNLOCK
#endif
}



void Thread::waitToComplete(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	if(Jezgro::running!=this->myPCB){
		if(this->myPCB->status==Zavrsen || this->myPCB==Jezgro::zaludna || this->myPCB==0){
			UNLOCK
			return;
		}
		myPCB->waitlista->dodajElem(Jezgro::running);
		Jezgro::running->status=Blokiran;
		dispatch();
		UNLOCK}
#endif


}




void Thread::sleep(Time time){
#ifndef BCC_BLOCK_IGNORE
	LOCK

	if(time>0){																//Napraviti podfunkciju koja ce da ubaci dati pcb u *sleep* listu, if veci oduzmi od njega i predji desno dok ne dodjes do manjeg i tu ubacis.
		Jezgro::running->sleepTime=time;									//Nakon ubacivanja treba refreshovati sve ostale elemente desno od ovog koji smo ubacili.
		Jezgro::uspavaj(Jezgro::running);									//Nakon ubacivanja timeSlice postavis umesto npr 9(x55) na 1(x55) u odnosu na to koliko si oduzimao pre njega
		Jezgro::running->status=Blokiran;
	}
	dispatch();
	UNLOCK
#endif
}



void dispatch(){
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	zahtevana_promena_konteksta = 1;
	Jezgro::timer();
	UNLOCK
	#endif
}



Thread::~Thread() {
	//waitToComplete();
//#ifndef BCC_BLOCK_IGNORE
//	LOCK
	//delete this->myPCB;
	//UNLOCK
//#endif
}

