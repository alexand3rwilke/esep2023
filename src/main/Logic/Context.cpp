/*
 * Context.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "Context.h"
#include "BasicState.h"
#include "RZ.h"

Context::Context() {
	state = new RZ(); // Idle State

}

Context::~Context() {
	delete state;
}

