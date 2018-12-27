/*
 * semaphor.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */

#include "semaphor.h"
#include "KerSem.h"
#include "jezgro.h"

Semaphore::Semaphore(int init){
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	myImpl=new KerSem(init);
	UNLOCK
	#endif
}

Semaphore::~Semaphore() {
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	delete myImpl;
	UNLOCK
	#endif
}

void Semaphore::signal(){
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	myImpl->signal();
	UNLOCK
	#endif
}

int Semaphore::wait(int toBlock){
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	int ret=myImpl->wait(toBlock);
	UNLOCK
	return ret;
	#endif
}

int Semaphore::val()const{
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	int ret= myImpl->val();
	UNLOCK
	return ret;
	#endif
}

