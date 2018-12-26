//
// Created by ofir8 on 12/20/18.
//

#include "IfCommand.h"
/**
 * the moethod checks if he condition is true, and if it is - runs all the commands
 */
void IfCommand::doCommand(){
	//If the Expression is true, go over the commands and excute them
    if (isTrue()) {
        for (Expression* c: commands) {
            c->calculate();
        }
    }
}
IfCommand::~IfCommand(){
	//Delete all the comannds
    for (Expression* c: commands) {
        delete(c);
    }
}