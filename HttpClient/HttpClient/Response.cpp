//
//  Response.cpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#include "Response.hpp"

/**
 * @brief Constructs a new Response object.
 *
 * @param statusCode The status code of the HTTP response.
 * @param headers The headers of the HTTP response.
 * @param responseText The body of the HTTP response.
 */
Response::Response(const long statusCode, const std::map<std::string, std::string>& headers, const std::string& responseText):statusCode_(statusCode), headers_(headers), responseText_(responseText) {};

/**
 * @brief Constructs a new Response object.
 *
 * @param statusCode The status code of the HTTP response.
 * @param headers The headers of the HTTP response (rvalue reference).
 * @param responseText The body of the HTTP response (rvalue reference).
 */
Response::Response(long statusCode, std::map<std::string, std::string>&& headers, std::string&& responseText):statusCode_(statusCode), headers_(headers), responseText_(responseText) {};

/**
 * @brief Outputs the HTTP response to an output stream.
 *
 * @param os The output stream.
 * @param response The Response object to output.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Response& response) {
    os << "Status Code: " << response.statusCode() << "\n";
    os << "Headers: \n";
    for (const auto& header : response.headers()) {
        os << header.first << ": " << header.second << "\n";
    }
    os << "Response Text: " << response.responseText();
    return os;
}

const nlohmann::json Response::getJsonResponse() const {
    nlohmann::json jsonData = nlohmann::json::parse(responseText_);
    return jsonData;
}
