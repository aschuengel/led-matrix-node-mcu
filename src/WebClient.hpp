#ifndef __WEBCLIENT_HPP__
#define __WEBCLIENT_HPP__

class Message {
private:
    char* _text;
public:
    const char* text() {
        return _text;
    }
};

class WebClient {
private:
public:
    Message readMessage();
};
#endif