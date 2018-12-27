/*
 * lista.h
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */

#ifndef LISTA_H_
#define LISTA_H_

#include "pcb.h"
#include "jezgro.h"

class Elem{
public:
	PCB *pcb;
	Elem *sled,*pret;
	Elem(PCB *pcb1){
		pcb=pcb1;
		sled=pret=0;
	}
};

class Lista {
public:
	Lista(){
		prvi=posl=0;
	}
	~Lista();
	void dodajElem(PCB *pcb);
	void dodajSleepElem(PCB *pcb, Elem *tek);
	PCB* uzmiElem();
	//void izbrisiElem(PCB *pcb);
private:
	Elem *prvi,*posl;


		friend class Jezgro;
		friend class PCB;
		friend class KerSem;
};

#endif /* LISTA_H_ */
