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

SystemState FSM::getCurrentState() const {
    return currentState;
}

void FSM::transitionToState(SystemState newState) {
    FSM::lastHeartbeat += FSM::delay; 
    FSM::currentState = newState;
}

void FSM::setDelay(uint32_t delay) {
    FSM::delay = delay;
}

void FSM::getDelay(uint32_t &delay) const {
    delay = FSM::delay;
}

void FSM::setErrorCount(int count) {
    FSM::errorCount = count;
}

int FSM::getErrorCount() const {
    return FSM::errorCount;
}

void FSM::setMoveCount(int count) {
    FSM::moveCount = count;
}

int FSM::getMoveCount() const {
    return FSM::moveCount;
}
