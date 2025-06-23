#include "ActionParamKey.hpp"

ActionParamKey::ActionParamKey(const std::string &a, const std::string &p) : action(a), parameter(p)
{
}

bool ActionParamKey::operator==(const ActionParamKey &other) const
{
    return action == other.action && parameter == other.parameter;
}

const std::string & ActionParamKey::get_action(void) const
{
    return this->action;
}

const std::string & ActionParamKey::get_parameter(void) const
{
    return this->parameter;
}