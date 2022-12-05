/*
 * Context.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "Context.h"
#include "BasicState.h"
#include "RZ/RZ.h"
#include "BZ/BZ.h"
#include "ESZ/ESz.h"
#include "SMZ/SMZ.h"
#include "FZ/FZ.h"

Context::Context() {
	state = new RZ(); // Idle State

}

Context::~Context() {
	delete state;
}

