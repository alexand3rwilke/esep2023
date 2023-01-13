/*
 * RZ.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_RZ_H_
#define SRC_MAIN_LOGIC_RZ_H_


#include "../Basestate.h"
#include "../BZ/BZ.h"
#include "../ESZ/ESZ.h"

#include "../SMZ/SMZ.h"





class RZ: public Basestate {
public:

    void entry() override;
    void exit() override;

    //void estp() override;
    void doAction(int, _pulse) override;

    void estp() override;

    //void estop();


};

#endif /* SRC_MAIN_LOGIC_RZ_H_ */
