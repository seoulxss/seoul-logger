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
	seoul_logger L1(seoul_logger::LOG_CONSOLE, seoul_logger::LOG_SUCCESSFUL);

	//Printing with "Suuccess" before the text and then also printing "Success!"
	L1.Print("Success!");

	//Set to false to hide the cur time
	L1.set_time_use(false);

	//True to show cur time
	L1.set_time_use(true);

	//set the log level
	L1.set_log_level(seoul_logger::LOG_WARNING);

	//Will print "WARNING" before the text
	L1.Print("Warning!");

	//This will create a Text file in the current folder    -> dont forget the .exe or whatever when u want to create it there
	//If u have a dll to inject somewhere, it will be created in the applications exe folder
	L1.Create_Log_File("Test_log_1", true, "", "Seoul_logger.exe");

	//This will create a Text file in a specific lcoation
	//As you can see, you can leave the "name_of_application" var empty, it will not affect anything
	//*WARNING* Don't ever put 0 or NULL or nullptr in these empty vars, it will crash!
	L1.Create_Log_File("Test_log_2", false, "C:\\Users\\teilo\\Desktop\\Test!", "");


	//Dont forget to set the log_mode after creating the file!
	//U still have to create a file if u init the Logger with LOG_FILE_AND_CONSOLE
	L1.set_log_mode(seoul_logger::LOG_FILE_AND_CONSOLE);




	//U can use this to shutdown the logger (Destroying)
	//But I woudln't recommend it unless you know what you're doing
	//The destructor will handle everything automatically
	//*WARNING*: Only Shutdown at the end of your program!
	//**************** READ LINE 94 ********************
	L1.Shutdown_Logger();




	//														//
	//														//
	//				More "Advanced functions"				//
	//														//
	//														//




	//Creating new logger
	seoul_logger L2(seoul_logger::LOG_CONSOLE, seoul_logger::LOG_SUCCESSFUL);

	//Sometimes you need to print values that arent strings, you can do that so:
	L2.Print("Example int: " + std::to_string(2));

	//This will not work!
	L2.Print("F: " + 2);

	//Sometimes you have a address which u want to print and it prints the dec version
	const int addr = 0x5555;
	L2.Print("Addr: " + std::to_string(addr));

	//You can fix this by using:
	//This will print the hex value of your variable
	L2.Print("Addr-hex: " + Logger::helper::value_to_string_hex<int>(addr));

	//you can do that also with dec numbers:
	L2.Print("Addr-dec: " + Logger::helper::value_to_string_dec(0x5555));




	//														//
	//														//
	//				Multiple logger objects					//
	//														//
	//														//




	//It is important, that the function Shutdown gets called at the end of the program.
	//The problem with multiple logger's is, that they are using the same handle to the console which gets closen when you shut them down
	//The destructor destroys everything at the end, so maybe it is better you never use the shutdown function.

	//					Example					//
	L1.Shutdown_Logger();
	L2.Shutdown_Logger();

	//Everything that gets printed here will be ignored (Even crash)
	//For example:
	std::cout << "This will not be printed! AND Maybe even crash!" << "\n";


	return 0;
}
