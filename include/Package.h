#ifndef DRONEDELIVERYSYSTEM_PACKAGE_HPP
#define DRONEDELIVERYSYSTEM_PACKAGE_HPP

#define MAX_PRIRORITY 5
#define MAX_ID 1000
#define MAX_WEIGHT 20

typedef struct {
	int priority;
	int id;
	int weight;
} Package;

/*------------------------------------------------------------------------*//**
 * @brief      Randomly creates a package.
 *
 * @return     returns a random package.
 */
Package createPackage();

#endif //DRONEDELIVERYSYSTEM_PACKAGE_HPP
