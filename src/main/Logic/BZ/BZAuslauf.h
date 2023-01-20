#ifndef SRC_MAIN_LOGIC_BZ_BZAUSLAUF_H_
#define SRC_MAIN_LOGIC_BZ_BZAUSLAUF_H_


#include "../Basestate.h"
#include "../BZ/BZ.h"



class BZAuslauf : public Basestate {
private:
	MQTTPublish *mqtt = new  MQTTPublish(contextData->disp,contextData);
public:

    void entry() override;
    void exit() override;
    void estp() override;
    void doAction(int, _pulse) override;
    //void showState() override;
};

#endif /* SRC_MAIN_LOGIC_BZ_BZAUSLAUF_H_ */
