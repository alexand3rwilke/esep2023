#ifndef SRC_MAIN_LOGIC_BZ_BZAUSSORTIERER_H_
#define SRC_MAIN_LOGIC_BZ_BZAUSSORTIERER_H_


#include "../Basestate.h"


class BZAussortierer : public Basestate {
public:

    void entry() override;
    void exit() override;
    void estp() override;
    void doAction(int) override;
    //void showState() override;
};

#endif /* SRC_MAIN_LOGIC_BZ_BZAUSSORTIERER_H_ */
