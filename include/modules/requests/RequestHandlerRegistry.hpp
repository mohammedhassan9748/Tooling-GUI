#ifndef REQUEST_HANDLER_REGISTRY_HPP 
#define REQUEST_HANDLER_REGISTRY_HPP

#include <memory>
#include <unordered_map>
#include "ActionParamKey.hpp"
#include "IRequestHandler.hpp"

class RequestHandlerRegistry {

private:

    std::unordered_map<ActionParamKey, std::unique_ptr<IRequestHandler>> request_handlers;

    RequestHandlerRegistry() = default;

public:

    // singleton
    static RequestHandlerRegistry& getInstance();

    void register_handler(const std::string&, const std::string&, std::unique_ptr<IRequestHandler>);

    IRequestHandler* get_request_handler(const std::string&, const std::string&) const;

};

#endif /* REQUEST_HANDLER_REGISTRY_HPP */
