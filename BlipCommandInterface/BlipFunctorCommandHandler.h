#pragma once

#include "BlipCommandHandler.h"

class BlipCommandLine;

#define BLIP_CMD_FUNC [](BlipCommandLine* commandLine, String command) -> void

typedef void (*BlipCmdFunc)(BlipCommandLine*, String);

class BlipFunctorCommandHandler : public BlipCommandHandler {
private:
    BlipCmdFunc handleFunctor;
public:
    BlipFunctorCommandHandler(BlipCommandLine* commandLine, BlipCmdFunc handleFunctor);
    void handle(String command);
};
