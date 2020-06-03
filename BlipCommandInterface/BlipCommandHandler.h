#pragma once

#ifdef ARDUINO
    #include "Arduino.h"
    class String;
#else
    #include <string>
    using namespace std;
    typedef string String;
#endif

class BlipCommandLine;

class BlipCommandHandler {
private: 
    BlipCommandLine* commandLine;
public:
    BlipCommandHandler(BlipCommandLine* _commandLine) : commandLine(_commandLine) {}

    virtual void handle(String command) = 0;
    virtual void onSet() {}

    BlipCommandLine* getBlipCommandLine() { return commandLine; }

    virtual ~BlipCommandHandler() {}
};

class BlipEmptyCommandHandler : public BlipCommandHandler {
public:
    BlipEmptyCommandHandler(BlipCommandLine* _commandLine)
        : BlipCommandHandler(_commandLine) {}
    void handle(String command) override {}
};
