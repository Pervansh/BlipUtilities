#include "BlipFunctorCommandHandler.h"
#include "BlipCommandLine.h"

BlipFunctorCommandHandler::BlipFunctorCommandHandler(BlipCommandLine* commandLine, BlipCmdFunc handleFunctor)
    : BlipCommandHandler(commandLine) {
    this->handleFunctor = handleFunctor;
}

void BlipFunctorCommandHandler::handle(String command) {
    handleFunctor(getBlipCommandLine(), command);
}
