#ifndef PREPRAREENTRY_H_
#define PREPRAREENTRY_H_
#include "ivtEntry.h"
#include "jezgro.h"

//Pravi novu prekidnu rutinu i smesta u numEntry ulaz i govori sta ona radi. U nasem slucaju zove signal i dispatch()s
#define PREPAREENTRY(numEntry,flag) \
void interrupt inter##numEntry(...); \
IVTEntry entry##numEntry(numEntry,inter##numEntry); \
void interrupt inter##numEntry(...){\
	entry##numEntry.signal(); \
	if(flag==1) entry##numEntry.callOld(); \
	dispatch();\
}
#endif
