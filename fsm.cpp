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

void FSM::addStateToHistory(SystemState state, uint32_t time) {
    FSM::stateHistory.push_back(std::make_pair(state, time));
}

vector<pair<SystemState, uint32_t>> FSM::getStateHistory() const {
    return FSM::stateHistory;
}

uint32_t FSM::getLastHeartbeat() const {
    return FSM::lastHeartbeat;
}

void FSM::setLastHeartbeat(uint32_t heartbeat) {
    FSM::lastHeartbeat = heartbeat;
}

void FSM::start() {
    FSM(1000);
}

void FSM::update() {
    switch(FSM::getCurrentState()) {
        case SystemState::INIT: return FSM::performInit();
        case SystemState::IDLE: return FSM::performProcess();
        case SystemState::MOVEMENT: return FSM::performMovement();
        case SystemState::SHOOTING: return FSM::performShooting();
        case SystemState::CALCULATION: return FSM::performCalculation();
        case SystemState::ERROR: return FSM::performErrorHandling();
        case SystemState::STOPPED: return FSM::shutdown();
    }
}

void FSM::performInit() {

}

void FSM::performProcess() {

}

void FSM::performMovement() {

}

void FSM::performShooting() {

}

void FSM::performCalculation() {

}

void FSM::performErrorHandling() {

}

void FSM::shutdown() {
    
}
