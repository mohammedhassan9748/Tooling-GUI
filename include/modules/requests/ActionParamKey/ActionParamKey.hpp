#ifndef ACTION_PARAM_KEY_HPP
#define ACTION_PARAM_KEY_HPP

#include <string>

class ActionParamKey{

private:
    std::string action;
    std::string parameter;

public:

    ActionParamKey() = delete;

    ActionParamKey(const std::string& a, const std::string& p);
    
    bool operator==(const ActionParamKey& other) const;
    
    const std::string& get_action(void) const;

    const std::string& get_parameter(void) const;

};

namespace std {
    template <>
    struct hash<ActionParamKey> {
        std::size_t operator()(const ActionParamKey& key) const {
            return std::hash<std::string>()(key.get_action())
                 ^ (std::hash<std::string>()(key.get_parameter()) << 1);
        }
    };
}

#endif /* ACTION_PARAM_KEY_HPP */
