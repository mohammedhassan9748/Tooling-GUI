#include "CmdConfig.hpp"
#include "RequestHandlerRegistry.hpp"

RequestHandlerRegistry &RequestHandlerRegistry::getInstance()
{
    static RequestHandlerRegistry instance;
    return instance;
}

void RequestHandlerRegistry::register_handler(const std::string& action, const std::string& param, std::unique_ptr<IRequestHandler> reqHandler)
{
    this->request_handlers.emplace(ActionParamKey(action, param), std::move(reqHandler));
}

IRequestHandler* RequestHandlerRegistry::get_request_handler(const std::string &action, const std::string &param) const
{
    auto it = this->request_handlers.find(ActionParamKey(action, param));
    if (it != this->request_handlers.end())
    {
        return it->second.get();
    }
    return nullptr;
}