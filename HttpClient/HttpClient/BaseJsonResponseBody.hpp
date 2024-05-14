//
//  BaseHttpResponseBody.hpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#ifndef BaseHttpResponseBody_hpp
#define BaseHttpResponseBody_hpp

#include <stdio.h>
#include "../json.hpp"

class BaseJsonResponseBody {
protected:
    long statusCode_;
    std::map<std::string, std::string> headers_;
public:
    BaseJsonResponseBody(const long statusCode, const std::map<std::string, std::string>& headers)
         : statusCode_(statusCode), headers_(std::move(headers)) {}
    BaseJsonResponseBody(long statusCode, std::map<std::string, std::string>&& headers)
         : statusCode_(statusCode), headers_(std::move(headers)) {}
    virtual ~BaseJsonResponseBody() = default;
    virtual void decode (const nlohmann::json& json) = 0;
};
#endif /* BaseHttpResponseBody_hpp */
