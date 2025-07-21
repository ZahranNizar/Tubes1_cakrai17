#include <stdio.h>
#include <stdlib.h>
#include "fsm.hpp"

FSM::FSM() : currentState(SystemState::INIT), lastHeartbeat(0), errorCount(0), stateHistory{} {
    
}

FSM::FSM(uint32_t delay) : currentState(SystemState::INIT), lastHeartbeat(0), errorCount(0), stateHistory{} {
    FSM::delay = delay;
}

FSM::~FSM() {
    FSM::stateHistory.clear();
}

