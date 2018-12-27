/*
 * KerSem.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */
#include "KerSem.h"

//int KerSem::idd=0;
int KerSem::cnt=0;

KerSem::KerSem(int init) {
//#ifndef BCC_BLOCK_IGNORE
//LOCK
	//id=idd++;
	value=init;
	lista=new Lista();
	//Jezgro::semLista->dodajElem(this);
	//UNLOCK
	//#endif
}


KerSem::~KerSem() {
	//#ifndef BCC_BLOCK_IGNORE
	//LOCK
	Elem* tek= lista->prvi;
	while(tek){
		PCB* temp=lista->uzmiElem();
		temp->status=Spreman;

		if(temp!=Jezgro::zaludna&&temp!=Jezgro::running){
			Scheduler::put(temp);
			tek=lista->prvi;
		}
	delete lista;
	//if(Jezgro::semLista)Jezgro::semLista->izbrisi(this);
	}
	//UNLOCK
	//#endif
}

int KerSem::wait(int toBlock){
	//#ifndef BCC_BLOCK_IGNORE
	//LOCK
	int ret0=0,ret1=1,ret2=-1;
	if(Jezgro::running!=Jezgro::zaludna){
	if(toBlock!=0){
		if(--value<0){
			Jezgro::running->status=Blokiran;
			lista->dodajElem(Jezgro::running);
			cnt++;

			//UNLOCK
			dispatch();
			return ret1;

		}else {
			//UNLOCK
			return ret0;
			}
	}
	else{
		if(value>0){
			--value;
			//UNLOCK
			return ret0;
		}
		else{
			if(value<=0){
				//UNLOCK
				return ret2;
			}
		}
	}}
	//UNLOCK
	//#endif


}

void KerSem::signal(){
	//#ifndef BCC_BLOCK_IGNORE
	//LOCK
	if(value++<0){
		PCB* temp=lista->uzmiElem();
		cnt--;
		temp->status=Spreman;
		Scheduler::put(temp);
	}
	//UNLOCK
	//#endif
}







int KerSem::val() const
{
	return value;
}
