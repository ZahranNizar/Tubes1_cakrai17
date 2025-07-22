#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
//#include <windows.h>
#include "fsm.hpp"

string StatusProgram(SystemState state){
    switch (state)
    {
    case SystemState::INIT: return "INIT";
    case SystemState::IDLE: return "IDLE";
    case SystemState::MOVEMENT: return "MOVEMENT";
    case SystemState::SHOOTING: return "SHOOTING";
    case SystemState::CALCULATION: return "CALCULATION";
    case SystemState::ERROR: return "ERROR";
    case SystemState::STOPPED: return "STOPPED";
    default: return "UNKNOWN";
    }
}

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
    FSM::currentState = newState;
    uint32_t waktu = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    FSM::setLastHeartbeat(waktu);
}

void FSM::setDelay(uint32_t delay) {
    //Sleep(delay);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
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
    uint32_t waktu_awal;
    if (FSM::getCurrentState() == SystemState::INIT) {
        waktu_awal = heartbeat;
    }
    FSM::lastHeartbeat = heartbeat - waktu_awal;
}

void FSM::start() {
    std::cout << "\nStarting FSM Program..." << std::endl;
    FSM::update();
    std::string command;
    std::string lower_command;

    while(true) {
        std::cout << "Here are the list of commands for this Program" << std::endl;
        std::cout << "(IDLE, MOVEMENT, SHOOTING, CALCULATION, STOPPED)" << std::endl;
        std::cout << "Please enter a command : ";
        std::getline(std::cin, command);
        std::transform(lower_command.begin(), lower_command.end(),lower_command.begin(), [](unsigned char c){ return std::tolower(c); });

        if (lower_command == "idle") {
            transitionToState(SystemState::IDLE);
        } else if (lower_command == "movement") {
            transitionToState(SystemState::MOVEMENT);
        } else if (lower_command == "shooting") {
            transitionToState(SystemState::SHOOTING);
        } else if (lower_command == "calculation") {
            transitionToState(SystemState::CALCULATION);
        } else if (lower_command == "stopped") {
            transitionToState(SystemState::STOPPED);
            break;
        } else {
            transitionToState(SystemState::ERROR);
        }

        FSM::update();

        FSM::addStateToHistory(getCurrentState(), getLastHeartbeat());        
        FSM::printStatus();
    }
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

void FSM::printStatus() {
    uint32_t delayPrint;
    getDelay(delayPrint);
    std::cout << "Status FSM : " << StatusProgram(getCurrentState()) << endl;
    std::cout << "Last Heartbeat Time : " << getLastHeartbeat() << endl;   
    std::cout << "Delay : " << delayPrint << endl;
    std::cout << "Error Count : " << getErrorCount() << endl;
}

void FSM::printStateHistory() {
    if (stateHistory.empty()) {
        std::cout << "No History of States ever recorded" << endl;
        return;
    }
    std::cout << "\n----- State History -----" << std::endl;
    for (size_t n = 0; n < stateHistory.size(); ++n) {
        std::cout << (n + 1) << ". State : " << StatusProgram(stateHistory[n].first)
                  << ", Heartbeat Time : " << stateHistory[n].second << endl;  
    }
    std::cout << "---------------------------" << std::endl;

}

void FSM::performInit() {
    uint32_t waktu = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    FSM::setLastHeartbeat(waktu);
    std::cout << "Initializing system..." << std::endl;
    FSM::addStateToHistory(getCurrentState(), getLastHeartbeat());

    setDelay(1000);
    transitionToState(SystemState::IDLE);
    
    printStatus();
    FSM::addStateToHistory(getCurrentState(), getLastHeartbeat());
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
