#ifndef SRC_MAIN_LOGIC_BZ_BZEINLAUF_H_
#define SRC_MAIN_LOGIC_BZ_BZEINLAUF_H_


#include "../Basestate.h"
#include "../BZ/BZ.h"



class BZEinlauf: public Basestate {
public:

    void entry() override;
    void exit() override;
    void estp() override;
    void doAction(int) override;
    //void showState() override;
};

#endif /* SRC_MAIN_LOGIC_BZ_BZEINLAUF_H_ */
