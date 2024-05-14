//
//  Response.hpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#ifndef Response_hpp
#define Response_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include "json.hpp"

class Response {
private:
    long statusCode_;
    std::map<std::string, std::string> headers_;
    std::string responseText_;
public:
    Response(const long statusCode, const std::map<std::string, std::string>& headers, const std::string& responseText);
    Response(long statusCode, std::map<std::string, std::string>&& headers, std::string&& responseText);

    const long statusCode() const;
    const std::map<std::string, std::string>& headers() const;
    const std::string& responseText() const;

    friend std::ostream& operator<<(std::ostream& os, const Response& response);
    const nlohmann::json getJsonResponse() const;
};

inline const long Response::statusCode() const {
    return statusCode_;
}

inline const std::map<std::string, std::string>& Response::headers() const {
    return headers_;
}

inline const std::string& Response::responseText() const {
    return responseText_;
}
#endif /* Response_hpp */
