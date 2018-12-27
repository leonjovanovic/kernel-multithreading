/*
 * event.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#include "event.h"
#include "jezgro.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo) {
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	myImpl=new KernelEv(ivtNo);
	UNLOCK
	#endif
}


Event::~Event() {
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	delete myImpl;
	UNLOCK
	#endif
}



void Event::wait(){
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	myImpl->wait();
	UNLOCK
	#endif
}


void Event::signal(){
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	myImpl->signal();
	UNLOCK
	#endif
}

