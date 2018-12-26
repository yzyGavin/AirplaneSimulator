//
// Created by ofir8 on 12/20/18.
//

#include "LoopCommand.h"

void LoopCommand::doCommand() {
    while (isTrue()) {
        for (Expression* c: commands) {
            c->calculate();
        }
    }
}
LoopCommand::~LoopCommand() {
    for (Expression* c: commands) {
        delete(c);
    }
}