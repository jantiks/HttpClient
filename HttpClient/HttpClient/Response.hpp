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

class Response {
private:
    long statusCode_;
    std::string headers_;
    std::string responseText_;
public:
    Response(const long statusCode, const std::string& headers, const std::string& responseText);
    Response(long statusCode, std::string&& headers, std::string&& responseText);

    const long statusCode() const;
    const std::string& headers() const;
    const std::string& responseText() const;
};

inline const long Response::statusCode() const {
    return statusCode_;
}

inline const std::string& Response::headers() const {
    return headers_;
}

inline const std::string& Response::responseText() const {
    return responseText_;
}
#endif /* Response_hpp */
