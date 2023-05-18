#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ENDL "\n"

#include <filesystem>
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>



#define COLOR_WHITE 15
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14







class Logger
{


	//Log Level section
public:
	enum LOG_LEVEL
	{
		LOG_ALL = 3,
		LOG_WARNING = 2,
		LOG_ERROR = 1,
		LOG_SUCCESSFUL = 0,

	};

	inline LOG_LEVEL get_log_level() const;
	LOG_LEVEL set_log_level(LOG_LEVEL new_log_level);

private:
	LOG_LEVEL log_level = LOG_ERROR;









	//log mode section
public:

	enum LOG_MODE
	{
		LOG_FILE_AND_CONSOLE = 2,
		LOG_FILE = 1,
		LOG_CONSOLE = 0,
	};

	inline LOG_MODE get_log_mode() const;
	LOG_MODE set_log_mode(LOG_MODE new_log_mode);

private:
	LOG_MODE log_mode = LOG_CONSOLE;










	//Time section

public:
	std::string get_current_time();
	std::string current_time = get_current_time();








	//Console section
private:
	HANDLE console_handle = nullptr;


public:
	HANDLE get_console_handle() const;
	HANDLE set_console_handle();
	bool close_console_handle();








	//function section

public:

	bool Init_Logger();
	bool Shutdown_Logger();
	void Print_log(std::string text);

	~Logger()
	{
		Shutdown_Logger();
	}











	//File section

	std::string get_exe_path();
	std::string get_exe_file_name();


	bool Create_Log_File(std::string log_file_name);
	std::ofstream get_current_file();




private:
	bool init_log = false;
	FILE* file_p;
	std::ofstream log_file;




};
