#include "Logger.h"


int main()
{
	//How to create the object
	//Gets init with console only & Successful level
	seoul_logger L1(seoul_logger::LOG_CONSOLE, seoul_logger::LOG_SUCCESSFUL);

	//Printing
	L1.Print("Success!");

	//Set to false to hide the cur time
	L1.set_time_use(false);

	//True to show cur time
	L1.set_time_use(true);

	//set the log level
	//Will print "WARNING" before the text
	L1.set_log_level(seoul_logger::LOG_WARNING);
	L1.Print("Warning!");

	//This will create a Text file in the current folder    -> dont forget the .txt
	//If u have a dll to inject somewhere, it will be created in the applications exe folder
	L1.Create_Log_File((std::string)"Kys", true, "", (std::string)"Seoul_logger.exe");

	//Dont forget to set the log_mode after creating the file!
	//U still have to create a file if u init the Logger with LOG_FILE_AND_CONSOLE
	L1.set_log_mode(seoul_logger::LOG_FILE_AND_CONSOLE);

	L1.Print("eeee!");



	//U can use this to shutdown the logger (Destroying)
	//But u can also don't call it
	//The destructor will handle everything automatically
	L1.Shutdown_Logger();


	return 0;
}
