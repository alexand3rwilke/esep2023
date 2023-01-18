#include "SimpleTimer.h"

SimpleTimer::SimpleTimer(Dispatcher *disp){
	this->disp = disp;
    resetTimer();
    stopStartHandler = new std::thread([this]() {stopStartThread();});
}

void SimpleTimer::startTimer() {
    if(is_paused) {
        is_paused = false;
        start_time = std::chrono::high_resolution_clock::now() - std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(paused_duration);
    } else {
        start_time = std::chrono::high_resolution_clock::now();
    }
}

void SimpleTimer::stopTimer() {
    if(!is_paused) {
        is_paused = true;
        auto end_time = std::chrono::high_resolution_clock::now();
        paused_duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
    }
}

void SimpleTimer::resumeTimer() {
    if(is_paused) {
        is_paused = false;
        start_time = std::chrono::high_resolution_clock::now() - std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(paused_duration);
    }
}

void SimpleTimer::resetTimer() {
    start_time = std::chrono::high_resolution_clock::time_point();
    is_paused = false;
    paused_duration = std::chrono::duration<double>::zero();
}

double SimpleTimer::getTime() {
    if (start_time == std::chrono::high_resolution_clock::time_point()) {
        return -1;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration;
    if(is_paused){
        duration = paused_duration;
    }else{
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
    }
    return duration.count();
}

void SimpleTimer::stopStartThread(){

	int chanID = ChannelCreate(0);
			if (chanID < 0) {
				perror("Could not create a channel!\n");
			}


			int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0);
			if (conID < 0) {
				perror("Could not connect to channel!");
			}
			std::vector<int8_t> events = {FA2_RUNNING,FA2_STOPPED};
			disp->registerForEventWIthConnection(events, conID);

			_pulse pulse;

			while(true) {

				int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

								if (recvid < 0) {
										perror("MsgReceivePulse failed!- in Timer");
										exit(EXIT_FAILURE);
								}

								   switch(pulse.code) {

								   case FA2_RUNNING:
									   printf("ALLES TIMER WERDEN GESTOPPT!");
									   if(FESTO_TYPE == 1) {



										   stopTimer();
									   }

								   	break;

								   	case FA2_STOPPED:
								   	 if(FESTO_TYPE == 1) {

								   		resumeTimer();
								   										   }

								   	break;

								}

			}






}
