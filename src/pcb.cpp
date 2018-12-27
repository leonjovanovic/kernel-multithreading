/*
 * pcb.cpp
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */
#include "jezgro.h"
#include <iostream.h>
#include <dos.h>
#include <stdlib.h>
#include "lock.h"

Lista* PCB::waitlista=0;

PCB::PCB(StackSize stackSize,Time timeSlice,Thread* thread) {
	//cout<<"inicPCB"<<endl;
	this->myThread=thread;
	this->size=stackSize;
	this->timeSlice=timeSlice;
	this->sleepTime=0;
	waitlista=new Lista();
	ss=0;
	sp=0;
	bp=0;
	stek=0;

	if (Jezgro::zaludna == 0) Jezgro::zaludna=this;
}



void PCB::inicSteka(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	//cout<<"inicSteka"<<endl;
	size/=sizeof(unsigned);
	stek=new unsigned[size];

	stek[size-1]=FP_SEG(this->myThread);
	stek[size-2]=FP_OFF(this->myThread);

	stek[size-5]=0x200;
	stek[size-6]=FP_SEG(&(wrapper));
	stek[size-7]=FP_OFF(&(wrapper));

	ss=FP_SEG(stek+size-16);
	sp=FP_OFF(stek+size-16);
	bp=sp;
	//cout<<"stek inicijalizovan\n";
	UNLOCK
	#endif
	Jezgro::running->stek = stek;
}



PCB::~PCB() {
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	if(waitlista) delete waitlista;
	if(stek!=0) delete stek;
	UNLOCK
	#endif
}



/*void PCB::wrapper(Thread* running){

}*/
void PCB::wrapper(){

	if(Jezgro::running->myThread==0 || Jezgro::running==0) return;
	Jezgro::running->myThread->run();

	//Elem *tek=Jezgro::running->myThread->myPCB->waitlista->prvi;
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	while(Jezgro::running->waitlista->prvi ){
		Jezgro::running->waitlista->prvi->pcb->status=Spreman;

		Scheduler::put(Jezgro::running->waitlista->prvi->pcb);

		Jezgro::running->waitlista->prvi=Jezgro::running->waitlista->prvi->sled;
	}
	Jezgro::running->status=Zavrsen;
	UNLOCK
	#endif
	dispatch();//Jezgro::running->myThread->myPCB->waitlista->prvi->pcb->status==Blokiran
}
