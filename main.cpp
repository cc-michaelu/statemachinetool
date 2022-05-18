#include <iostream>
#include <memory>
#include <map>
#include <string>
#include "StateMachineManager.h"

using namespace std;

bool mfg_to_registered() {
    std::cout << "Transition from mfg to registered" << std::endl;
    return true;
}

bool registered_to_associated() {
    std::cout << "Transition from registered to associated" << std::endl;
    return true;
}

bool associated_to_mfg() {
    std::cout << "Transition from associated to manufactured" << std::endl;
    return true;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    StateMachineManager mgr("StateMachine");

    mgr.addState("MANUFACTURED",
                 { nodeInitializer{"REGISTERED", mfg_to_registered} });
    mgr.addState("REGISTERED",
                 { nodeInitializer{"USER_ASSOCIATED", registered_to_associated}});
    mgr.addState("USER_ASSOCIATED",
                 { nodeInitializer{"MANUFACTURED", associated_to_mfg}});

    if (mgr.setState("MANUFACTURED")) {
        std::cout << "State is manufactured" << std::endl;

        if (mgr.setState("USER_ASSOCIATED")) {
            std::cout << "Should not be possible" << std::endl;
        } else {
            std::cout << "State is " << mgr.getState() << std::endl;
        }

        if (mgr.setState("REGISTERED")) {
            std::cout << "Transitioned to registered" << std::endl;
        }
        if (mgr.setState("USER_ASSOCIATED")) {
            std::cout << "Transitioned to associated" << std::endl;
        }
        if (mgr.setState("REGISTERED")) {
            std::cout << "Transitioned to registered" << std::endl;
        }
    }

    return 0;
}
