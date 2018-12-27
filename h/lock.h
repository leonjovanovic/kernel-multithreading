/*
 * lock.h
 *
 *  Created on: Aug 14, 2018
 *      Author: OS1
 */

#ifndef LOCK_H_
#define LOCK_H_

volatile static unsigned int lockFlag=1;

#define lock {lockFlag=0;}
#define unlock {lockFlag=1;}




#endif /* LOCK_H_ */
