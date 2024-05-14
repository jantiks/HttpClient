//
//  Response.cpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#include "Response.hpp"

Response::Response(const std::string& statusCode, const std::string& headers, const std::string& responseText):statusCode_(statusCode), headers_(headers), responseText_(responseText) {};

Response::Response(std::string&& statusCode, std::string&& headers, std::string&& responseText):statusCode_(statusCode), headers_(headers), responseText_(responseText) {};
