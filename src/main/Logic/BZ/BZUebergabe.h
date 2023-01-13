
#ifndef SRC_MAIN_LOGIC_BZ_BZUEBERGABE_H_
#define SRC_MAIN_LOGIC_BZBZUEBERGABE_H_


#include "../Basestate.h"
#include "../BZ/BZ.h"



class BZUebergabe: public Basestate {
public:

    void entry() override;
    void exit() override;
    void estp() override;
    void doAction(int, _pulse) override;
    //void showState() override;
};

#endif /* SRC_MAIN_LOGIC_BZ_BZUEBERGABE_H_ */
