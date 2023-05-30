#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <filesystem>
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>


namespace Logger
{

	namespace LOG_COLOR
	{
		constexpr unsigned int COLOR_WHITE = 15;
		constexpr unsigned int COLOR_RED = 12;
		constexpr unsigned int COLOR_GREEN = 10;
		constexpr unsigned int COLOR_YELLOW = 14;


	}

	namespace LOG_MACRO
	{
		constexpr char ENDL[] = "\n";


	}

	namespace helper
	{
		bool ShowMessageBox(const char* Text, const char* Title, bool beep);

		template<typename Type>
		std::string value_to_string_hex(Type value)
		{
			std::stringstream hex_val_ss;
			hex_val_ss << "0x" << std::hex << value;
			std::string HexVal = hex_val_ss.str();
			return HexVal;
		}

		template<typename Type>
		std::string value_to_string_dec(Type value)
		{
			std::stringstream val_ss;
			val_ss << std::dec << value;
			std::string Val = val_ss.str();
			return Val;
		}

	}





}


class seoul_logger
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
	bool Console_already_There = false;

private:
	[[nodiscard]] HANDLE get_console_handle() const;
	HANDLE set_console_handle();









	//function section
public:

	bool Init_Logger();
	bool Shutdown_Logger();


	void Print(const std::string &text);


	bool already_down = false;

	~seoul_logger()
	{
		if (already_down == false)
			Shutdown_Logger();

		else
			return;
	}

	seoul_logger(LOG_MODE wish_log_mode, LOG_LEVEL wish_log_level) : log_mode(wish_log_mode), log_level(wish_log_level)
	{
		Init_Logger();
	}


	






	//File section
private:
	std::string get_exe_file_name();

public:
	bool Create_Log_File(const std::string log_file_name, bool in_directory, std::string Location, std::string name_of_application);
	[[nodiscard]] std::ofstream get_current_file();




private:
	inline static bool init_log = false;
	FILE* file_p;
	std::ofstream log_file;









};
