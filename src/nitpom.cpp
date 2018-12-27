/*
 * nitpom.cpp
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */

#include "thread.h"
#include "nitpom.h"



NitPom::NitPom() {
	radi=1;
}



NitPom::~NitPom() {
	radi=0;
	waitToComplete();
}



void NitPom::run(){
	while(radi);
}

