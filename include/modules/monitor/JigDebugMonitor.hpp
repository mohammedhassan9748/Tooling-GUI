#ifndef JIG_DEBUG_MONITOR_HPP
#define JIG_DEBUG_MONITOR_HPP

#include <string>
#include <functional>

class JigDebugMonitor
{
public:
    JigDebugMonitor(const std::string& jigID);

    void set_on_debug_data_callback(std::function<void(const std::string&)> callback);

private:

    const std::string jig_debug_topic;

    std::string current_debug_data;
    
    std::function<void(const std::string&)> on_debug_data_cb;
};

#endif // JIG_DEBUG_MONITOR_HPP

