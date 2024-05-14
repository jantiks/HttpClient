# HttpClient Project Documentation

## Overview

This project is a C++ HTTP client library designed to make HTTP requests. The client supports basic HTTP methods like GET, POST, PUT, and DELETE, making it suitable for a wide range of HTTP-based applications.

## Features

- **HTTP Methods**: Supports GET, POST, PUT, and DELETE methods.
- **Custom Headers**: Allows setting custom HTTP headers.
- **JSON Handling**: Decodes JSON responses using the nlohmann::json library.
- **Error Handling**: Throws exceptions on failed HTTP requests.

## Dependencies

- **libcurl**: .
- **nlohmann::json**: A modern C++ library for handling JSON data.

## File Structure

- `HttpClient.hpp`: 
- `HttpClient.cpp`: Implementation file for the `HttpClient` class.
- `BaseJsonResponseBody.hpp`: Base class handling JSON response bodies.
- `Response.hpp`: Base class for generic textual responses
- `json.hpp`: Header file for the nlohmann::json library (included directly to the project).

## Classes and Methods

### HttpClient

#### Public Methods

- `static Response Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod, const std::string& requestBody = "")`
  - Sends an HTTP request and returns the response.
  - Parameters:
    - `url`: The URL to send the request to.
    - `headers`: A vector of headers to include in the request.
    - `requestMethod`: The HTTP method to use (GET, POST, PUT, DELETE).
    - `requestBody`: The body of the request (used for POST and PUT).

- `static void Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod, BaseJsonResponseBody& responseBody, const std::string& requestBody = "")`
  - Sends an HTTP request and decodes the JSON response into a provided `BaseJsonResponseBody` object.
  - Parameters:
    - `url`: The URL to send the request to.
    - `headers`: A vector of headers to include in the request.
    - `requestMethod`: The HTTP method to use (GET, POST, PUT, DELETE).
    - `responseBody`: The object to decode the JSON response into.
    - `requestBody`: The body of the request (used for POST and PUT).

#### Private Methods

- `static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)`
  - Callback function for libcurl to write data.
  - Parameters:
    - `contents`: The pointer to the delivered data.
    - `size`: The size of a data member.
    - `nmemb`: The number of data members.
    - `userp`: The user-defined pointer to store the result.

- `static Response performRequest(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod, const char* postData = nullptr)`
  - Performs the HTTP request using libcurl.
  - Parameters:
    - `url`: The URL to send the request to.
    - `headers`: A vector of headers to include in the request.
    - `requestMethod`: The HTTP method to use (GET, POST, PUT, DELETE).
    - `postData`: The body of the request (used for POST and PUT).

- `static std::map<std::string, std::string> parseHeaders(const std::string& fromString)`
  - Parses HTTP headers from a string into a map.
  - Parameters:
    - `fromString`: The string containing the headers.

### Response

#### Public Methods

- `Response(const long statusCode, const std::map<std::string, std::string>& headers, const std::string& responseText)`
  - Constructs a new `Response` object.
  - Parameters:
    - `statusCode`: The status code of the HTTP response.
    - `headers`: The headers of the HTTP response.
    - `responseText`: The body of the HTTP response.

- `Response(long statusCode, std::map<std::string, std::string>&& headers, std::string&& responseText)`
  - Constructs a new `Response` object.
  - Parameters:
    - `statusCode`: The status code of the HTTP response.
    - `headers`: The headers of the HTTP response (rvalue reference).
    - `responseText`: The body of the HTTP response (rvalue reference).

- `const long statusCode() const`
  - Gets the status code of the HTTP response.
  - Returns: The status code.

- `const std::map<std::string, std::string>& headers() const`
  - Gets the headers of the HTTP response.
  - Returns: The headers.

- `const std::string& responseText() const`
  - Gets the body of the HTTP response.
  - Returns: The body.

- `friend std::ostream& operator<<(std::ostream& os, const Response& response)`
  - Outputs the HTTP response to an output stream.
  - Parameters:
    - `os`: The output stream.
    - `response`: The `Response` object to output.

- `const nlohmann::json getJsonResponse() const`
  - Gets the JSON representation of the HTTP response body.
  - Returns: The JSON representation.

### BaseJsonResponseBody

#### Public Methods

- `BaseJsonResponseBody(const long statusCode, const std::map<std::string, std::string>& headers)`
  - Constructs a new `BaseJsonResponseBody` object.
  - Parameters:
    - `statusCode`: The status code of the HTTP response.
    - `headers`: The headers of the HTTP response.

- `BaseJsonResponseBody(long statusCode, std::map<std::string, std::string>&& headers)`
  - Constructs a new `BaseJsonResponseBody` object.
  - Parameters:
    - `statusCode`: The status code of the HTTP response.
    - `headers`: The headers of the HTTP response (rvalue reference).

- `virtual ~BaseJsonResponseBody() = default`
  - Virtual destructor.

- `virtual void decode(const nlohmann::json& json) = 0`
  - Decodes the JSON response.
  - Parameters:
    - `json`: The JSON object to decode.

## Usage

### Example

```cpp
#include "HttpClient.hpp"
#include "BaseJsonResponseBody.hpp"
#include <iostream>

class MyJsonResponseBody : public BaseJsonResponseBody {
public:
    MyJsonResponseBody(long statusCode, const std::map<std::string, std::string>& headers)
        : BaseJsonResponseBody(statusCode, headers) {}

    void decode(const nlohmann::json& json) override {
        // Implement JSON decoding logic here
        std::cout << "Decoded JSON: " << json.dump() << std::endl;
    }
};

int main() {
    std::vector<std::string> headers = { "Content-Type: application/json" };
    MyJsonResponseBody responseBody(0, headers);

    try {
        HttpClient::Request("http://example.com/api", headers, HTTPMethod::GET, responseBody);
    } catch (const std::runtime_error& e) {
        std::cerr << "HTTP request failed: " << e.what() << std::endl;
    }

    return 0;
}
