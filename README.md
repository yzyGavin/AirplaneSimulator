# Airplane Simulator Interpreter

Welcome to our script interpreter for the flight simulator - [FlightGear](http://home.flightgear.org/)
![FlightGear Simulator](http://wiki.flightgear.org/images/thumb/6/65/Beechcraft_B1900D.JPG/800px-Beechcraft_B1900D.JPG)

Our interpreter can read the script direct from the console or either from file (given to the main by argument)

## How to use:
upload soon
## List of commands:

 - **OpenDataServer** *[port] [hz]* - open server to listen to the simulator
 - **Connect** *[ip] [port]* - connect to the simulator to send commands
 - **var** *[name]* = *[Expression/ bind [address]]* - set var of Expression or bind it to var from the simulator
 - **print** *[Expression/ var]* - print the expression or the value of the var
 - **sleep** *[int]* - sleep for milliseconds
 - **if** *[condition]* { 
	 *[commands]*
 } - condition if
 
 - **while** *[condition]* {
	*[commands]*
 } - while condition.
 - **exit** - only for input from console (in file, exit after excute all the commands).
