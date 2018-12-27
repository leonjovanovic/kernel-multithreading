/*
 * pcb.h
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "jezgro.h"
#include "lista.h"
#include "lock.h"
#include "KerSem.h"
#include "KernelEv.h"

enum Status {Spreman, Blokiran, Zavrsen};


class PCB {

private:
	PCB(StackSize stackSize,Time timeSlice,Thread* thread);
	~PCB();
	Status status;
	unsigned int ss,sp,bp;
	unsigned* stek;
	Time timeSlice;
	Time sleepTime;
	Thread *myThread;
	StackSize size;

	void inicSteka();

	friend class Thread;
	friend class Jezgro;
	friend class KerSem;
	friend class KernelEv;
public:
	static void wrapper();
	static Lista *waitlista;
};




#endif /* PCB_H_ */
