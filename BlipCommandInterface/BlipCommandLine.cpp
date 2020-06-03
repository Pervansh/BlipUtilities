#include "BlipCommandLine.h"
#include "BlipCommandHandler.h"
#include "BlipFunctorCommandHandler.h"
#include <iostream>

namespace blip {
    bool strEquals(String s1, String s2);
}

#ifdef ARDUINO
    bool blip::strEquals(String s1, String s2) {
        return s1.equals(s2);
    }
#else
    bool blip::strEquals(String s1, String s2) {
        return !s1.compare(s2);
    }
#endif

BlipCommandLine::BlipCommandLine()
    : emptyHandler(new BlipEmptyCommandHandler(this)) {
    handler = emptyHandler;
    main = new BlipFunctorCommandHandler(this, BLIP_CMD_FUNC {
        if (blip::strEquals(command, "ch")) {
            commandLine->setHandler(commandLine->getEmptyHandler());
        } else if (commandLine->getHandler() == commandLine->getEmptyHandler()) {
            Vector<HandlerPair>* pairs = commandLine->getHandlerTriggers();
            for (unsigned int i = 0; i < pairs->size(); ++i) {
                if (blip::strEquals(command, (*pairs)[i].trigger)) {
                    commandLine->setHandler((*pairs)[i].handler);
                    break;
                }
            }
        }
    });
}

BlipCommandLine::BlipCommandLine(BlipCommandHandler* _main)
    : main(_main), emptyHandler(new BlipEmptyCommandHandler(this)) {
    handler = emptyHandler;
}

void BlipCommandLine::addHandler(BlipCommandHandler* handler, String handlerTrigger) {
    handlerTriggers.push_back(HandlerPair(handler, handlerTrigger));
}

void BlipCommandLine::sendCommand(String command) {
    main->handle(command);
    handler->handle(command);
}

void BlipCommandLine::setHandler(BlipCommandHandler* handler) {
    this->handler = handler;
    handler->onSet();
}

BlipCommandLine::~BlipCommandLine() {
    for (unsigned int i = 0; i < handlerTriggers.size(); ++i) {
        delete handlerTriggers[i].handler;
    }
    delete main;
    delete emptyHandler;
}
