#include "jezgro.H"
#include "iostream.h"

extern int userMain(int argc, char* argv[]);


int main(int argc, char* argv[]){

	Jezgro::inic();

	int i= userMain(argc, argv);

	Jezgro::restore();

	return i;

}
