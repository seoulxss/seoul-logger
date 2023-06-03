#include "Logger.h"


int main()
{
	//											//
	//											//
	//				Basic Functions				//
	//											//
	//											//



	//How to create the object
	//Gets init with console only & Successful level
	Cseoul_logger L1(Cseoul_logger::LOG_CONSOLE, Cseoul_logger::LOG_SUCCESSFUL);
	//Printing with "Suuccess" before the text and then also printing "Success!"
	L1.Print("Success!");

	//Set to false to hide the cur time
	L1.set_time_use(false);

	//True to show cur time
	L1.set_time_use(true);

	//set the log level
	L1.set_log_level(Cseoul_logger::LOG_WARNING);

	//Will print "WARNING" before the text
	L1.Print("Warning!");

	//This will create a Text file in the current folder    -> dont forget the .exe or whatever when u want to create it there
	//If u have a dll to inject somewhere, it will be created in the applications exe folder
	L1.Create_Log_File("Test_log_1", true, "", "Cseoul_logger.exe");

	//This will create a Text file in a specific lcoation
	//As you can see, you can leave the "name_of_application" var empty, it will not affect anything
	//*WARNING* Don't ever put 0 or NULL or nullptr in these empty vars, it will crash!
	L1.Create_Log_File("Test_log_2", false, "C:\\Users\\teilo\\Desktop\\Test!", "");


	//Dont forget to set the log_mode after creating the file!
	//U still have to create a file if u init the Logger with LOG_FILE_AND_CONSOLE
	L1.set_log_mode(Cseoul_logger::LOG_FILE_AND_CONSOLE);




	//U can use this to shutdown the logger (Destroying)
	//But I woudln't recommend it unless you know what you're doing
	//The destructor will handle everything automatically
	//*WARNING*: Only Shutdown at the end of your program!
	//**************** READ LINE 120 ********************
	L1.Shutdown_Logger();




	//														//
	//														//
	//				More "Advanced" functions				//
	//														//
	//														//




	//Creating new logger
	Cseoul_logger L2(Cseoul_logger::LOG_CONSOLE, Cseoul_logger::LOG_SUCCESSFUL);

	//Sometimes you need to print values that arent strings, you can do that so:
	L2.Print("Example int: " + std::to_string(2));

	//This will not work -> acts like an array!
	L2.Print("F1: " + 2);

	//This will also not work -> acts like an array!
	L2.Print("F2: " + 0x222);

	//This will also not work -> acts like an array!
	int some_addr = 0x2323;
	L2.Print("F3: " + some_addr);

	//Sometimes you have a address which u want to print and it prints the dec version
	const int addr = 0x5555;
	L2.Print("Addr: " + std::to_string(addr));

	//You can fix this by using:
	//This will print the hex value of your variable
	L2.Print("Addr-hex: " + Logger::helper::value_to_string_hex<int>(addr));

	//you can do that also with dec numbers:
	L2.Print("Addr-dec: " + Logger::helper::value_to_string_dec(0x5555));

	std::cout << CCounter<Cseoul_logger>::Oustanding_Objects() << "STF" << Logger::LOG_MACRO::ENDL;


	//														//
	//														//
	//				Multiple logger objects					//
	//														//
	//														//


	//If u want to use multiple logger, init them all at ones!
		//					Example					//

	Cseoul_logger First_Logger(Cseoul_logger::LOG_CONSOLE, Cseoul_logger::LOG_SUCCESSFUL);
	Cseoul_logger Second_Logger(Cseoul_logger::LOG_CONSOLE, Cseoul_logger::LOG_SUCCESSFUL);


	//this is how you should NOT do it:
	Cseoul_logger First_Logger_(Cseoul_logger::LOG_CONSOLE, Cseoul_logger::LOG_SUCCESSFUL);
	// code....
	// code....
	Cseoul_logger Second_Logger_(Cseoul_logger::LOG_CONSOLE, Cseoul_logger::LOG_SUCCESSFUL);
	// code...


	//It is important, that the function Shutdown gets called at the end of the program.
	//The destructor destroys everything at the end, so maybe it is better you never use the shutdown function.

	//					Example					//
	L1.Shutdown_Logger();
	L2.Shutdown_Logger();
	//Everything that gets printed here will be ignored (Even crash)
	//For example:
	//std::cout << "This will not be printed! AND Maybe even crash!" << "\n";


	return 0;
}
