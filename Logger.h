#pragma once
#define _CRT_SECURE_NO_WARNINGS    //Dangerous

#include <filesystem>
#include <windows.h>
#include <string>
#include <fstream>


	//														//
	//														//
	//						Seoul logger V2					//
	//														//
	//														//


//helper functions
namespace Logger
{

	//You can use this
	namespace helper
	{

		template<typename Type>
		constexpr std::string value_to_string_hex(const Type& value)
		{
			std::stringstream hex_val_ss;
			hex_val_ss << "0x" << std::hex << value;
			std::string HexVal = hex_val_ss.str();
			return HexVal;
		}

		template<typename Type>
		constexpr std::string value_to_string_dec(const Type& value)
		{
			std::stringstream val_ss;
			val_ss << std::dec << value;
			std::string Val = val_ss.str();
			return Val;
		}

	}



}

//Private functions (Don't use)
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
		constexpr bool ShowMessageBox(const char* Text, const char* Title, bool beep=true);


	}


}

//A class which counts the objects of the logger class
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



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/* Logging class */


class Cseoul_logger : private CCounter<Cseoul_logger>
{


public:
	//														//
	//														//
	/*					Log Level section					*/
	//														//
	//														//

	enum LOG_LEVEL 
	{
		LOG_GENERAL = 3,
		LOG_WARNING = 2,
		LOG_ERROR = 1,
		LOG_SUCCESSFUL = 0,
	};

	[[nodiscard]] constexpr LOG_LEVEL get_log_level() const &;
	LOG_LEVEL set_log_level(LOG_LEVEL new_log_level) &;



	//														//
	//														//
	/*					Log mode section					*/
	//														//
	//														//				
	
	enum LOG_MODE
	{
		LOG_FILE_AND_CONSOLE = 2,
		LOG_FILE = 1,
		LOG_CONSOLE = 0,
	};

	[[nodiscard]] constexpr LOG_MODE get_log_mode() const &;
	LOG_MODE set_log_mode(LOG_MODE new_log_mode) &;



	//														//
	//														//
	/*						Time section					*/
	//														//
	//														//	
	

	//set to true, to show the current time before the message
	//set to false to hide it
	bool set_time_use(const bool& val) &;



	//														//
	//														//
	/*						Console section					*/
	//														//
	//														//	
	//EMPTY



	//														//
	//														//
	/*						File section					*/
	//														//
	//														//	



	//This will create a .txt with a specific name
	//log_file_name = this will be the name of the .txt
	//in_directory = should it be in the exe's path? true / false
	//Location = Put here the location if in_directory is FALSE if its true, leave it with ""
	//name_of_application = Put the exe process name here with the ".exe"
	bool Create_Log_File(const std::string& log_file_name, bool in_directory, std::string Location, const std::string& name_of_application) &;


private:
	//														//
	//														//
	/*					Log Level section					*/
	//														//
	//														//

	LOG_LEVEL m_log_level_ = LOG_ERROR;



	//														//
	//														//
	/*					Log mode section					*/
	//														//
	//														//	

	LOG_MODE m_log_mode_ = LOG_CONSOLE;



	//														//
	//														//
	/*						Time section					*/
	//														//
	//														//	

	bool m_use_time_ = true;

	static std::string get_current_time();
	constexpr bool get_time_use() const;


	//														//
	//														//
	/*						Console section					*/
	//														//
	//				

	HANDLE* m_console_handle_ = nullptr;
	bool m_console_already_there_ = false;

	bool close_console_handle() const;
	[[nodiscard]] constexpr HANDLE* get_console_handle() const;
	HANDLE* set_console_handle() &;



	//														//
	//														//
	/*						File section					*/
	//														//
	//														//	

	bool m_init_log_ = false;
	FILE* m_file_p_;
	std::ofstream m_log_file_;
	std::string m_log_file_location_;

	constexpr std::string get_log_file_loc() const;
	std::string set_log_file_loc(const std::string& new_loc) & noexcept;

	static std::string get_exe_file_name() noexcept;



	//														//
	//														//
	/*					Main Func Section					*/
	//														//
	//														//	
public:

	//This will init the logger
	//You don't need to call this, since it gets called automatically
	bool Init_Logger() noexcept;

	//THis will shutdown the logger
	//You don't need to call this, it will be called automatically
	//WARNING: It is adviceable to watch the Example.cpp!!!!!
	bool Shutdown_Logger() noexcept;

	//This will print the string in the Console or file or both!
	//If u want to print other things, see the Example.cpp
	void Print(const std::string &text); 

	explicit Cseoul_logger(LOG_MODE wish_log_mode = LOG_MODE::LOG_CONSOLE, LOG_LEVEL wish_log_level = LOG_LEVEL::LOG_ERROR) : m_log_level_(wish_log_level), m_log_mode_(wish_log_mode)
	{
		Init_Logger();
	}

	~Cseoul_logger() noexcept
	{
		if (m_already_down_ == false)
			Shutdown_Logger();

		else
			return;
	}




private:
	bool m_already_down_ = false;










};



