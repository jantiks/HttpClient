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

/**
 * @brief A class representing an HTTP response. (Not neccisseraly JSON response, any textual response)
 */
class Response {
private:
    long statusCode_; ///< The status code of the HTTP response.
    std::map<std::string, std::string> headers_; ///< The headers of the HTTP response.
    std::string responseText_; ///< The body of the HTTP response.

public:
    /**
     * @brief Constructs a new Response object.
     *
     * @param statusCode The status code of the HTTP response.
     * @param headers The headers of the HTTP response.
     * @param responseText The body of the HTTP response.
     */
    Response(const long statusCode, const std::map<std::string, std::string>& headers, const std::string& responseText);

    /**
     * @brief Constructs a new Response object.
     *
     * @param statusCode The status code of the HTTP response.
     * @param headers The headers of the HTTP response (rvalue reference).
     * @param responseText The body of the HTTP response (rvalue reference).
     */
    Response(long statusCode, std::map<std::string, std::string>&& headers, std::string&& responseText);

    /**
     * @brief Gets the status code of the HTTP response.
     *
     * @return const long The status code.
     */
    const long statusCode() const;

    /**
     * @brief Gets the headers of the HTTP response.
     *
     * @return const std::map<std::string, std::string>& The headers.
     */
    const std::map<std::string, std::string>& headers() const;

    /**
     * @brief Gets the body of the HTTP response.
     *
     * @return const std::string& The body.
     */
    const std::string& responseText() const;

    /**
     * @brief Outputs the HTTP response to an output stream.
     *
     * @param os The output stream.
     * @param response The Response object to output.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Response& response);

    /**
     * @brief Gets the JSON representation of the HTTP response body.
     *
     * @return const nlohmann::json The JSON representation.
     */
    const nlohmann::json getJsonResponse() const;
};

/**
 * @brief Gets the status code of the HTTP response
 *
 * @return const long The status code.
 */
inline const long Response::statusCode() const {
    return statusCode_;
}

/**
 * @brief Gets the headers of the HTTP response
 *
 * @return const std::map<std::string, std::string>& The headers
 */
inline const std::map<std::string, std::string>& Response::headers() const {
    return headers_;
}

/**
 * @brief Gets the body of the HTTP response
 *
 * @return const std::string& The body
 */
inline const std::string& Response::responseText() const {
    return responseText_;
}

#endif /* Response_hpp */
