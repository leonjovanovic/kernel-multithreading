/*
 * ivtEntry.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#include "ivtEntry.h"
#include <dos.h>
#include <stdlib.h>
#include <IOSTREAM.H>
IVTEntry* IVTEntry::ivTable[256];


IVTEntry::IVTEntry(IVTNo ivtNum,InterruptO Nova) {	//pravimo novi ulaz u iv tabeli sa zadatim brojem ulaza i novom prekidnom rutinom koju treba da podmetnemo
	#ifndef BCC_BLOCK_IGNORE
	LOCK
	ivTable[ivtNum]=this;
	this->ivtNum=ivtNum;
	this->myEvent=0;

	Old=getvect(this->ivtNum); //uzima rutiu sa uaza ivtNum i stavlja u Old prekidnu rutinu
	setvect(this->ivtNum,Nova);	//postavljamo novu prekidnu rutinu na taj ulaz
	UNLOCK
	#endif

}

IVTEntry::~IVTEntry() {
	ivTable[ivtNum] = 0;
	#ifndef BCC_BLOCK_IGNORE
	LOCK

	setvect(this->ivtNum,Old);

	UNLOCK
	#endif
}


void IVTEntry::signal(){
	if(this->myEvent)
		this->myEvent->signal();
	dispatch();
}

void IVTEntry::callOld(){
	//pozivamo staru prekidnu rutinu
		Old();

}
