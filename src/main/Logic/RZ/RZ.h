/*
 * RZ.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_RZ_H_
#define SRC_MAIN_LOGIC_RZ_H_

#include "../BasicState.h"

class RZ : public BasicState {
public:
    void entry() override;
    void exit() override;
    void estp() override;
    void doAction() override;
    //void showState() override;
};

#endif /* SRC_MAIN_LOGIC_RZ_H_ */
