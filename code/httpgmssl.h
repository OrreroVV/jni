#ifndef __HTTPGMSSL_H__
#define __HTTPGMSSL_H__

#include <string>

enum HttpType {
GET,
POST,
};

void ssl_send_data_request(std::string url, std::string cookie, HttpType httpType, std::string post_data, std::string* res);

#endif