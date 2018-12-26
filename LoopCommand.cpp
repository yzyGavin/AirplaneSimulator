//
// Created by ofir8 on 12/20/18.
//

#include "LoopCommand.h"
/**
 * the method checks if the condition is true, and while it is true, calls all the "doCommand" methods of the commands.
 */
void LoopCommand::doCommand() {
	//If the Expression is true, go over the commands and excute them
    while (isTrue()) {
        for (Expression* c: commands) {
            c->calculate();
        }
    }
}
LoopCommand::~LoopCommand() {
	//Delete all the comannds
    for (Expression* c: commands) {
        delete(c);
    }
}