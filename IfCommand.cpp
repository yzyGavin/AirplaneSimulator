//
// Created by ofir8 on 12/20/18.
//

#include "IfCommand.h"

void IfCommand::doCommand(){
    if (isTrue()) {
        for (Expression* c: commands) {
            c->calculate();
        }
    }
}
IfCommand::~IfCommand(){
    for (Expression* c: commands) {
        delete(c);
    }
}