/*
 * Program:		world.cxx
 * Author:		Chris Langford
 * Date:		2014/05/07
 * Description:		The World class is a container for a Library and all Systems that interact with it
 */

#include <vector>
#include <typeinfo>
#include <iostream>
#include <memory>

#include "world.h"
#include "library.h"
#include "system.h"

using namespace CLD_ECS;

//------------------------------------------------------------------------------

/*
 * Function:		addSystem()
 * Description:		Adds a new System to the systems vector
 * Arguments:
 * 	System* s:	A new System
 * Returns:		none
 */

void World::addSystem(System* s) {
	//if systems isn't empty, we need to check it for possibly duplicate entries before adding a new System
	if(systems.size() != 0) {
		//a simple iterator for looping through systems
		std::vector<std::unique_ptr<System>>::iterator i;
		//if a single System of s's type is found, return from the function without adding anything
		for(i = systems.begin(); i < systems.end(); ++i) {
			if(&typeid(*(*i)) == &typeid(*s)) {
				//the System already exists in systems, so we quit
				std::cerr<<"addSystem() WARNING: world already contains a System of type "<<typeid(*s).name()<<std::endl;
				return;
			}
		}
	}
	//if systems is empty or has no Systems of s's type, add the new System
	std::cerr<<"addSystem() ALERT: adding System "<<typeid(*s).name()<<std::endl;
	systems.push_back(std::unique_ptr<System>(s));
}

//------------------------------------------------------------------------------

/*
 * Function:		systemsInit()
 * Description:		Runs the init() function on each System in systems
 * Arguments:		none
 * Returns:		none
 */

void World::systemsInit() {
	//a simple iterator for looping through systems
	std::vector<std::unique_ptr<System>>::iterator i;
	//loop through systems, checking for a System of type T
	for(i = systems.begin(); i < systems.end(); ++i) {
		std::cerr<<"systemsInit() ALERT: initializing system "<<typeid(*i).name()<<std::endl;
		(*i)->init(&library);
	}
}

//------------------------------------------------------------------------------

/*
 * Function:		systemsUpdate()
 * Description:		Runs the update() function on each System in systems
 * Arguments:		none
 * Returns:		none
 */

void World::systemsUpdate() {
	//a simple iterator for looping through systems
	std::vector<std::unique_ptr<System>>::iterator i;
	//loop through systems, checking for a System of type T
	for(i = systems.begin(); i < systems.end(); ++i){
		std::cerr<<"systemsUpdate() ALERT: updating system "<<typeid(*i).name()<<std::endl;
		(*i)->update();
	}
}
