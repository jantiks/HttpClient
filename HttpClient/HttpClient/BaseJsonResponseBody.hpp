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
    /**
     * @brief Constructs a new BaseJsonResponseBody object.
     *
     * @param statusCode The status code of the HTTP response.
     * @param headers The headers of the HTTP response.
     */
    BaseJsonResponseBody(const long statusCode, const std::map<std::string, std::string>& headers)
         : statusCode_(statusCode), headers_(std::move(headers)) {}

    /**
     * @brief Constructs a new BaseJsonResponseBody object.
     *
     * @param statusCode The status code of the HTTP response.
     * @param headers The headers of the HTTP response (rvalue reference).
     */
    BaseJsonResponseBody(long statusCode, std::map<std::string, std::string>&& headers)
         : statusCode_(statusCode), headers_(std::move(headers)) {}

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
};

#endif /* BaseHttpResponseBody_hpp */
