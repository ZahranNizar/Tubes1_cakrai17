#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cctype>
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

FSM::FSM() : currentState(SystemState::INIT), lastHeartbeat(0), errorCount(0), moveCount(0),stateHistory{} {
    uint32_t waktu_awal;
}

FSM::FSM(uint32_t delay) : currentState(SystemState::INIT), lastHeartbeat(0), errorCount(0), moveCount(0), stateHistory{} {
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
    //std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    auto start_time = std::chrono::system_clock::now();
    while (true) {
        auto current_time = std::chrono::system_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
        if (elapsed_time > delay) {
            break;
        }
    }
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
    if (FSM::getCurrentState() == SystemState::INIT) {
        FSM::lastHeartbeat = heartbeat;
    } else {
        FSM::lastHeartbeat = heartbeat - stateHistory[0].second;
    }
}

void FSM::start() {
    FSM();
    std::cout << "\nStarting FSM Program..." << std::endl;
    FSM::update();

    bool programRunning(true);

    while(programRunning) {
        
        performProcess();

        if (FSM::getCurrentState() == SystemState::STOPPED) {
            programRunning = false;
        }

    }

}

void FSM::update() {
    
    uint32_t waktu = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    FSM::setLastHeartbeat(waktu);
    FSM::addStateToHistory(getCurrentState(), getLastHeartbeat());    
    
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
    std::cout << "Delay : " << delayPrint << " ms" << endl;
    std::cout << "Error Count : " << getErrorCount() << endl;
}

void FSM::printStateHistory() {
    if (stateHistory.empty()) {
        std::cout << "No History of States ever recorded" << endl;
        return;
    }
    std::cout << "\n----- State History -----" << std::endl;
    for (size_t n = 0; n < stateHistory.size(); ++n) {
        if (n == 0) {
            std::cout << (n + 1) << ". State : " << StatusProgram(stateHistory[n].first)
                      << ", Heartbeat Time : " << 0 << " ms" << endl;    
        } else if (n == stateHistory.size() - 1) {
            std::cout << (n + 1) << ". State : " << StatusProgram(stateHistory[n].first)
                      << ", Heartbeat Time : " << stateHistory[n].second << " ms (Now)" << endl;
        } else {
            std::cout << (n + 1) << ". State : " << StatusProgram(stateHistory[n].first)
                      << ", Heartbeat Time : " << stateHistory[n].second << " ms" << endl; 
        } 
    }
    std::cout << "---------------------------" << std::endl;

}

void FSM::performInit() {
    uint32_t waktu_awal = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    FSM::setLastHeartbeat(waktu_awal);
    std::cout << "Initializing system..." << std::endl;

    setDelay(1000);
    transitionToState(SystemState::IDLE);

    printStatus();
    FSM::addStateToHistory(getCurrentState(), getLastHeartbeat());
}

void FSM::performProcess() {
    std::string lower_command;
    FSM::setDelay(FSM::delay);
    

    std::cout << "\n------------------------------------------------" << std::endl;
    std::cout << "Here are the list of commands for this Program" << std::endl;
    std::cout << "(IDLE, MOVEMENT, SHOOTING, CALCULATION, STOPPED)" << std::endl;
    std::cout << "Please enter a command : ";
    std::getline(std::cin, lower_command);
    std::cout << "------------------------------------------------\n" << std::endl;
    
    std::transform(lower_command.begin(), lower_command.end(),lower_command.begin(), [](unsigned char c){ return std::tolower(c); });

    if (lower_command == "idle") {
        transitionToState(SystemState::IDLE);
        FSM::printStatus();
        FSM::printStateHistory();
    } else if (lower_command == "movement") {
        transitionToState(SystemState::MOVEMENT);
    } else if (lower_command == "shooting") {
        transitionToState(SystemState::SHOOTING);
    } else if (lower_command == "calculation") {
        transitionToState(SystemState::CALCULATION);
    } else if (lower_command == "stopped") {
        transitionToState(SystemState::STOPPED);
    } else {
        transitionToState(SystemState::ERROR);
    }

    FSM::update();
       
}

void FSM::performMovement() {
    FSM::setDelay(FSM::delay);
    std::cout << "Moving..." << endl;
    FSM::setMoveCount(++FSM::moveCount);
    std::cout << "Movement Count : " << getMoveCount() << endl;

    if (FSM::moveCount == 3) {
        FSM::transitionToState(SystemState::SHOOTING);
        FSM::update();
    } else {
        FSM::transitionToState(SystemState::IDLE);
        FSM::update();
    }
}

void FSM::performShooting() {
    FSM::setDelay(FSM::delay);
    std::cout << "Shooting..." << endl;
    FSM::setMoveCount(0);
    std::cout << "Movement Count : " << getMoveCount() << endl;

    FSM::transitionToState(SystemState::IDLE);    
}

void FSM::performCalculation() {
    FSM::setDelay(FSM::delay);
    std::cout << "Performing Calculation..." << endl;
    if (FSM::moveCount == 0) {
        FSM::transitionToState(SystemState::ERROR);
        FSM::update();
    } else if (FSM::moveCount > 0) {
        FSM::transitionToState(SystemState::IDLE);
        FSM::update();
    }
}

void FSM::performErrorHandling() {
    FSM::setDelay(FSM::delay);
    std::cout << "Error occurred, performing error handling..." << endl;
    FSM::setErrorCount(++FSM::errorCount);
    std::cout << "Error Count : " << getErrorCount() << endl;
    
    if (FSM::errorCount > 3) {
        FSM::setDelay(FSM::delay);
        FSM::transitionToState(SystemState::STOPPED);
        FSM::update();
    } else {
        FSM::setDelay(FSM::delay);
        FSM::transitionToState(SystemState::IDLE);
        FSM::update();
    }
}

void FSM::shutdown() {
    FSM::setDelay(FSM::delay);
    std::cout << "System stopped, shutting down..." << endl;
    FSM::setDelay(FSM::delay);
}
