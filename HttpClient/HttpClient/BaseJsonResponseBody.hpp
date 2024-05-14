//
//  BaseHttpResponseBody.hpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#ifndef BaseHttpResponseBody_hpp
#define BaseHttpResponseBody_hpp

#include <stdio.h>
#include <map>
#include "../json.hpp"

/**
 * @brief A base class for handling JSON response bodies.
 */
class BaseJsonResponseBody {
protected:
    long statusCode_; ///< The status code of the HTTP response.
    std::map<std::string, std::string> headers_; ///< The headers of the HTTP response.

public:
    BaseJsonResponseBody(){}

    /**
     * @brief Virtual destructor.
     */
    virtual ~BaseJsonResponseBody() = default;

    /**
     * @brief Decodes the JSON response.
     *
     * @param json The JSON object to decode.
     */
    virtual void decode (const nlohmann::json& json) = 0;

    void setStatusCode(long statusCode) {
        statusCode_ = statusCode;
    }

    void setHeaders(const std::map<std::string, std::string>& headers) {
        headers_ = headers;
    }
};

#endif /* BaseHttpResponseBody_hpp */
