//
// Created by michael_uman on 5/6/22.
//

#ifndef STATEMACHINETOOL_STATEMACHINEMANAGER_H
#define STATEMACHINETOOL_STATEMACHINEMANAGER_H


#include <string>
#include <map>
#include <functional>
#include <initializer_list>
#include <memory>
#include <vector>

using stateCb = std::function<bool()>;
using stateMap = std::map<std::string, stateCb>;

struct nodeInitializer {
    std::string state;
    stateCb cb;
};

class StateMachineManager;

class StateMachineNode {
public:
    explicit StateMachineNode(const std::string &nodeName, std::initializer_list<nodeInitializer> initlist);
    virtual ~StateMachineNode();

    bool canTransition(const std::string &state);

private:
    friend class StateMachineManager;

    std::string nodeName;
    stateMap states;
};

class StateMachineManager {
public:
    explicit StateMachineManager(const std::string &machineName);
    virtual ~StateMachineManager();

    void addState(const std::string &nodeName, std::initializer_list<nodeInitializer> initlist);

    bool setState(const std::string &state);
    std::string getState() const;

private:
    StateMachineNode * findNode(const std::string &nodeName);
    std::string machinename;
    std::vector<std::unique_ptr<StateMachineNode>> states;

    StateMachineNode * current_state = nullptr;
};



#endif //STATEMACHINETOOL_STATEMACHINEMANAGER_H
