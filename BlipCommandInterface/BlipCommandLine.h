#pragma once

#ifdef ARDUINO
    #include "Arduino.h"
    #include <Vector.h>
    class String;
#else
    #include <vector>
    #include <string>
    using namespace std;
    typedef string String;
    #define Vector vector
    // using Vector = vector<class T>;
#endif

class BlipCommandHandler;

struct HandlerPair {
    BlipCommandHandler* handler;
    String trigger;

    HandlerPair (BlipCommandHandler* _handler, String _trigger)
        : handler(_handler), trigger(_trigger) {}
};

class BlipCommandLine {
private:
    BlipCommandHandler* handler;
    BlipCommandHandler* main;
    BlipCommandHandler* emptyHandler;
    Vector<HandlerPair> handlerTriggers;
public:

    BlipCommandLine();
    BlipCommandLine(BlipCommandHandler* _main);
    
    void addHandler(BlipCommandHandler* handler, String handlerTrigger);
    Vector<HandlerPair>* getHandlerTriggers() { return &handlerTriggers; }
    void setHandler(BlipCommandHandler* handler);
    BlipCommandHandler* getHandler() { return handler; }
    BlipCommandHandler* getEmptyHandler() { return emptyHandler; }

    void sendCommand(String command);

    ~BlipCommandLine();
};

