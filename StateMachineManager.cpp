//
// Created by michael_uman on 5/6/22.
//
#include <iostream>
#include "StateMachineManager.h"

StateMachineManager::StateMachineManager(const std::string &machineName) : machinename(machineName) {

}

StateMachineManager::~StateMachineManager() {

}

void StateMachineManager::addState(const std::string &nodeName, std::initializer_list<nodeInitializer> initlist) {
    states.push_back(std::unique_ptr<StateMachineNode>(new StateMachineNode(nodeName, initlist)));
}

bool StateMachineManager::setState(const std::string &state) {
    bool result = false;

    if (current_state == nullptr) {
        if (auto stateNode = findNode(state)) {
            current_state = stateNode;
            result = true;
        } else {
            std::cerr << "Unable to set state \'" << state << "\'" << std::endl;
        }
    } else {
        // check if the current state can transition to new state.
        if (current_state->canTransition(state)) {
             result = current_state->states[state]();
             current_state = findNode(state);
        } else {
            std::cerr << "Unable to make transition to '" << state << "'" << std::endl;
        }
    }

    return result;
}

StateMachineNode *StateMachineManager::findNode(const std::string &nodeName) {
    for (const auto &stateNode : states) {
        if (stateNode->nodeName == nodeName) {
            return stateNode.get();
        }
    }
    return nullptr;
}

std::string StateMachineManager::getState() const {
    std::string state;

    if (current_state != nullptr) {
        state = current_state->nodeName;
    }

    return state;
}


StateMachineNode::StateMachineNode(const std::string &nodeName,
                                   std::initializer_list<nodeInitializer> initlist) : nodeName(nodeName) {
    for (const auto& inititem : initlist) {
        states[inititem.state] = inititem.cb;
    }
}

StateMachineNode::~StateMachineNode() {

}

bool StateMachineNode::canTransition(const std::string &state) {
    for (const auto &stateItem : states) {
        if (stateItem.first == state) {
            return true;
        }
    }

    return false;
}
