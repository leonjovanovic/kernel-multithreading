/*
 * KerSem.h
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "semaphor.h"
#include "lista.h"
#include "jezgro.h"
#include "pcb.h"
//#include "listaSem.h"
class Lista;
//class ListaSem;

class KerSem{
public:
	KerSem(int init);
	virtual ~KerSem();

	void signal();
	int wait(int toBlock);
	int val() const;

private:
	int value;
	Lista* lista;
	//static int idd;
	static int cnt;
	//int id;
};

#endif /* KERSEM_H_ */
