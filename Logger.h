#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <filesystem>
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>

	//														//
	//														//
	//						Seoul logger V2					//
	//														//
	//														//



namespace Logger
{

	//You can use this
	namespace helper
	{

		template<typename Type>
		constexpr std::string value_to_string_hex(Type value)
		{
			std::stringstream hex_val_ss;
			hex_val_ss << "0x" << std::hex << value;
			std::string HexVal = hex_val_ss.str();
			return HexVal;
		}

		template<typename Type>
		constexpr std::string value_to_string_dec(Type value)
		{
			std::stringstream val_ss;
			val_ss << std::dec << value;
			std::string Val = val_ss.str();
			return Val;
		}

	}



}

namespace priv_logger
{

		//You should never use this
	namespace LOG_COLOR__
	{
		constexpr unsigned short int COLOR_WHITE = 15;
		constexpr unsigned short int COLOR_RED = 12;
		constexpr unsigned short int COLOR_GREEN = 10;
		constexpr unsigned short int COLOR_YELLOW = 14;
	}

	//You should never use this
	namespace LOG_MACRO__
	{
		constexpr char ENDL[] = "\n";

	}

	namespace helper
	{
		bool ShowMessageBox(const char* Text, const char* Title, bool beep=true);


	}


}

template<class Type>
class CCounter
{
public:
	CCounter()
	{
		++total;
	}

	//CCounter(const CCounter& Type);

	~CCounter()
	{
		--total;
	}

	static size_t Oustanding_Objects();




private:
	static size_t total;


};

template <class Type>
size_t CCounter<Type>::Oustanding_Objects()
{
	return total;
}

template<class Type>
size_t CCounter<Type>::total = 0;

class Cseoul_logger : private CCounter<Cseoul_logger>
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
	static std::string get_current_time();
	std::string current_time = get_current_time();
	bool use_time = true;

public:
	//set to true, to show the current time before the message
	//set to false to hide it
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

	//This will print the string in the Console or file or both!
	//If u want to print other things, see the Example.cpp
	void Print(const std::string &text);


	bool already_down = false;

	~Cseoul_logger()
	{
		if (already_down == false)
			Shutdown_Logger();

		else
			return;
	}

	Cseoul_logger(LOG_MODE wish_log_mode=LOG_MODE::LOG_CONSOLE, LOG_LEVEL wish_log_level=LOG_LEVEL::LOG_ERROR) : log_mode(wish_log_mode), log_level(wish_log_level)
	{
		Init_Logger();
	}


	






	//File section
private:
	std::string get_exe_file_name();


public:
	//This will create a .txt with a specific name
	//log_file_name = this will be the name of the .txt
	//in_directory = should it be in the exe's path? true / false
	//Location = Put here the location if in_directory is FALSE if its true, leave it with ""
	//name_of_application = Put the exe process name here with the ".exe"
	bool Create_Log_File(const std::string log_file_name, bool in_directory, std::string Location, std::string name_of_application);
	[[nodiscard]] std::ofstream get_current_file();




private:
	inline static bool init_log = false;
	FILE* file_p;
	std::ofstream log_file;
	std::string log_file_location;









};

