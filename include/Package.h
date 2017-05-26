#ifndef DRONEDELIVERYSYSTEM_PACKAGE_HPP
#define DRONEDELIVERYSYSTEM_PACKAGE_HPP

typedef struct {
	int priority;
	int id;
	int weight;
} Package;

Package createPackage();
#endif //DRONEDELIVERYSYSTEM_PACKAGE_HPP
