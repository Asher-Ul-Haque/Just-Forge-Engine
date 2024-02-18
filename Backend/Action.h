#ifndef SUPERMARIO_ACTION_H
#define SUPERMARIO_ACTION_H
#include <string>

class Action
{
    std::string aName;
    std::string aType;

// - - - - - - - - - -
public:
    Action();
    Action(const std::string &NAME, const std::string& TYPE);
    const std::string& getName() const { return aName; };
    const std::string & getType() const { return aType; };
};

#endif //SUPERMARIO_ACTION_H
