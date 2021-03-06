#ifndef AUTH_H
#define AUTH_H

#include "cipher.hpp"

#include <string>
#include <unordered_set>

/**
   Forward declaration
 **/
struct bufferevent;

class Auth
{
public:
    enum class State { incomplete, success, failed, error, waitUserPassAuth };
    
    Auth(const Cryptor &cryptor, bufferevent *inConn);

    Auth(const Cryptor &cryptor, bufferevent *inConn,
         const std::string &username, const std::string &password);
    
    // disable the copy operations    
    Auth(const Auth &) = delete;
    Auth &operator=(const Auth &) = delete;

    State authenticate();
    State validateUsernamePassword();
    
private:
    static constexpr unsigned char      SOCKS5_VERSION          = 0x05;    

    static constexpr unsigned char      AUTH_NONE               = 0x00;
    static constexpr unsigned char      AUTH_USER_PASSWORD      = 0x02;        
    static constexpr unsigned char      AUTH_NO_ACCEPTABLE      = 0xFF;

    static constexpr unsigned char      USER_AUTH_VERSION       = 0x01;
    static constexpr unsigned char      USER_AUTH_SUCCESS       = 0x00;
    static constexpr unsigned char      USER_AUTH_FAILED        = 0x01;    

    Cryptor                             cryptor_;
    bufferevent                         *inConn_;
    unsigned char                       authMethod_;
    std::unordered_set<unsigned char>   supportMethods_;
    std::string                         username_;
    std::string                         password_;
};

#endif /* AUTH_H */
