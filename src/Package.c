#include <stdlib.h>
#include <time.h>
#include "Package.h"

Package createPackage() {
	return (Package) {rand()%MAX_PRIRORITY, rand()%MAX_ID, rand()%MAX_WEIGHT} ;
}

