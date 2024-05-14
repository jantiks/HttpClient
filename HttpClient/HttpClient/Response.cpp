//
//  Response.cpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#include "Response.hpp"

Response::Response(const long statusCode, const std::map<std::string, std::string>& headers, const std::string& responseText):statusCode_(statusCode), headers_(headers), responseText_(responseText) {};

Response::Response(long statusCode, std::map<std::string, std::string>&& headers, std::string&& responseText):statusCode_(statusCode), headers_(headers), responseText_(responseText) {};

std::ostream& operator<<(std::ostream& os, const Response& response) {
    os << "Status Code: " << response.statusCode() << "\n"
//       << "Headers: " << response.headers() << "\n"
       << "Response Text: " << response.responseText();
    return os;
}
