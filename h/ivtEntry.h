/*
 * ivtEntry.h
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "jezgro.h"
#include "event.h"
#include "lista.h"
#include "pcb.h"
#include "KernelEv.h"
typedef void interrupt (*InterruptO)(...);
typedef unsigned char IVTNo;
class KernelEv;
class IVTEntry {

public:

	IVTEntry(IVTNo ivtNum,InterruptO Nova);
	virtual ~IVTEntry();
	void callOld();
	void signal();

private:

	static IVTEntry *ivTable[];
	IVTNo ivtNum;
	KernelEv *myEvent;
	InterruptO Old;
	friend class KernelEv;
};

#endif /* IVTENTRY_H_ */
