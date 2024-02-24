#ifndef SUPERMARIO_ACTION_H
#define SUPERMARIO_ACTION_H
#include <string>
//---------------------------------

class Action
{
    //Data
    std::string aName;
    std::string aType;
// - - - - - - - - - -
public:
    //Construction
    Action();
    Action(const std::string &NAME, const std::string& TYPE);
    //---------------------------------

    //METHODS-
    const std::string& getName() const { return aName; };
    const std::string & getType() const { return aType; };
};
//---------------------------------

#endif //SUPERMARIO_ACTION_H
