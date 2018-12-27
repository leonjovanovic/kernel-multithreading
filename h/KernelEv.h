/*
 * KernelEv.h
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "event.h"
#include "ivtEntry.h"
#include "lista.h"
#include "jezgro.h"
#include "pcb.h"


/*#define PREPAREENTRY(numEntry,flag)\
void interrupt inter##numEntry(...);\
IVTEntry newEntry##numEntry(numEntry,&inter##numEntry);\
void interrupt inter##numEntry(){\
	newEntry##numEntry.signal();\
	if ( flag == 1)\
		newEntry##numEntry.callOld();\
		dispatch();\
}*/
typedef unsigned char IVTNo;

class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
	virtual ~KernelEv();
	void signal();
	void wait();
private:
	int value;
	PCB* blokirana;
	PCB* kreator;
	IVTNo ulaz;

};

#endif /* KERNELEV_H_ */
