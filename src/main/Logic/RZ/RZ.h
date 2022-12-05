/*
 * RZ.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_RZ_H_
#define SRC_MAIN_LOGIC_RZ_H_

<<<<<<< HEAD:src/main/Logic/RZ/RZ.h
#include "../BasicState.h"

class RZ : public BasicState {
=======
#include "BaseState.h"

class RZ: public BaseState {
>>>>>>> dev:src/main/Logic/RZ.h
public:
    void entry() override;
    void exit() override;
    void estp() override;
    void doAction() override;
    //void showState() override;
};

#endif /* SRC_MAIN_LOGIC_RZ_H_ */
