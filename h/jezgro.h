/*
 * jezgro.h
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */

#ifndef JEZGRO_H_
#define JEZGRO_H_

#include "thread.h"
#include "pcb.h"
#include "lista.h"
#include "nitpom.h"
#include "lock.h"
#include "semaphor.h"
#include "KerSem.h"
#include "KernelEv.h"
#include "event.h"


#include "SCHEDULE.h"
#include <iostream.h>
#include <dos.h>
#include <stdlib.h>

#define LOCK asm {pushf; cli;}
#define UNLOCK {asm popf;}


extern volatile int zahtevana_promena_konteksta;
typedef void interrupt (*InterruptO)(...);
//#define lock Jezgro::lockFlag=0;
//#define unlock Jezgro::lockFlag=1;


class Lista;
class Thread;
class Jezgro {
public:
	static PCB *running;
	static PCB *zaludna;
	static NitPom *zaludnaNit;
	static Lista *sleeplista;
	static InterruptO Stara;

	static void uspavaj(PCB *myPCB);
	static void interrupt timer(...);

	static void inic();
	static void restore();
	static void probudi();

	static int brojac;
	static int test;
	//volatile static unsigned int lockFlag;

	friend class PCB;
	friend class Thread;
	friend class KerSem;
	friend class KernelEv;
	friend class event;

};


#endif /* JEZGRO_H_ */
