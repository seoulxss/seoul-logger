#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <filesystem>
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>

constexpr unsigned int COLOR_WHITE = 15;
constexpr unsigned int COLOR_RED = 12;
constexpr unsigned int COLOR_GREEN = 10;
constexpr unsigned int COLOR_YELLOW = 14;
constexpr char ENDL[] = "\n";


class Logger
{
	//Log Level section
public:
	enum LOG_LEVEL 
	{
		LOG_GENERAL = 3,
		LOG_WARNING = 2,
		LOG_ERROR = 1,
		LOG_SUCCESSFUL = 0,
	};

	[[nodiscard]] inline LOG_LEVEL get_log_level() const;
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

	[[nodiscard]] inline LOG_MODE get_log_mode() const;
	LOG_MODE set_log_mode(LOG_MODE new_log_mode);

private:
	LOG_MODE log_mode = LOG_CONSOLE;










	//Time section
private:
	std::string get_current_time();
	std::string current_time = get_current_time();
	bool use_time = true;

public:
	bool set_time_use(const bool val);
	bool get_time_use() const;







	//Console section
private:
	HANDLE console_handle = nullptr;
	bool close_console_handle() const;

public:
	[[nodiscard]] HANDLE get_console_handle() const;
	HANDLE set_console_handle();









	//function section
public:

	bool Init_Logger();
	bool Shutdown_Logger();


	void Print_log(const std::string &text);

	~Logger()
	{
		Shutdown_Logger();
	}

	Logger(LOG_MODE wish_log_mode, LOG_LEVEL wish_log_level) : log_mode(wish_log_mode), log_level(wish_log_level)
	{
		Init_Logger();
	}


	






	//File section
private:
	[[nodiscard]] std::string get_exe_path();
	std::string get_exe_file_name();

public:
	bool Create_Log_File(const std::string &log_file_name);
	[[nodiscard]] std::ofstream get_current_file();




private:
	inline static bool init_log = false;
	FILE* file_p;
	std::ofstream log_file;




};
