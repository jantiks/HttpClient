//
//  Response.cpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#include "Response.hpp"

Response::Response(const long statusCode, const std::string& headers, const std::string& responseText):statusCode_(statusCode), headers_(headers), responseText_(responseText) {};

Response::Response(long statusCode, std::string&& headers, std::string&& responseText):statusCode_(statusCode), headers_(headers), responseText_(responseText) {};
