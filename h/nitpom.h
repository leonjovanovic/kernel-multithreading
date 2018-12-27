/*
 * nitpom.h
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */

#ifndef NITPOM_H_
#define NITPOM_H_

#include "thread.h"

class NitPom : public Thread{
public:
	NitPom();
	~NitPom();
	int radi;
	void run();

};

#endif /* NITPOM_H_ */
