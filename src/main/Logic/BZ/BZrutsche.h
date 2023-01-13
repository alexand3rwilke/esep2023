#ifndef SRC_MAIN_LOGIC_BZ_BZRUTSCHE_H_
#define SRC_MAIN_LOGIC_BZ_BZRUTSCHE_H_


#include "../Basestate.h"
#include "../BZ/BZ.h"



class BZrutsche: public Basestate {
public:

    void entry() override;
    void exit() override;
    void estp() override;
    void doAction(int, _pulse) override;
    //void showState() override;
};

#endif /* SRC_MAIN_LOGIC_BZ_BZRUTSCHE_H_ */
