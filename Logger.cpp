#include "Logger.h"

bool Logger::helper::ShowMessageBox(const char* Text, const char* Title, bool beep)
{
	if (beep == true)
	{
		MessageBeep(MB_ICONERROR);
		MessageBoxA(nullptr, Text, Title, MB_ICONERROR);
		return true;
	}

	else
	{
		MessageBoxA(nullptr, Text, Title, MB_ICONERROR);
		return true;
	}
}

inline seoul_logger::LOG_LEVEL seoul_logger::get_log_level() const
{
	return seoul_logger::log_level;
}

seoul_logger::LOG_LEVEL seoul_logger::set_log_level(LOG_LEVEL new_log_level)
{
	return seoul_logger::log_level = new_log_level;
}

inline seoul_logger::LOG_MODE seoul_logger::get_log_mode() const
{
	return seoul_logger::log_mode;
}

seoul_logger::LOG_MODE seoul_logger::set_log_mode(LOG_MODE new_log_mode)
{
	return seoul_logger::log_mode = new_log_mode;
}

std::string seoul_logger::get_current_time()
{
	std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
    time_t t_time_t = std::chrono::system_clock::to_time_t(t);
    
    std::tm* local_time = std::localtime(&t_time_t);
    std::ostringstream oss;

	 oss << std::put_time(local_time, "%H:%M:%S");

	return oss.str();
}

bool seoul_logger::set_time_use(const bool val)
{
	seoul_logger::use_time = val;
	return seoul_logger::use_time;
}

bool seoul_logger::get_time_use() const
{
	return seoul_logger::use_time;
}

HANDLE seoul_logger::get_console_handle() const
{
	return seoul_logger::console_handle;
}

HANDLE seoul_logger::set_console_handle()
{
	return seoul_logger::console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

//Make sure to call Create_log_file when u want to log into a file!
//This also gehts called automatically, so no need to call it again.
bool seoul_logger::Init_Logger()
{
    if (seoul_logger::init_log == false)
        seoul_logger::init_log = true;

    if (seoul_logger::get_log_mode() == LOG_CONSOLE || seoul_logger::get_log_mode() == LOG_FILE_AND_CONSOLE)
    {

		if (seoul_logger::get_console_handle() != nullptr)
			Console_already_There = true;

		if (seoul_logger::get_console_handle() == nullptr)
		{
			AllocConsole();
			freopen_s(&file_p, "CONOUT$", "w", stdout);

		}


    	if (seoul_logger::get_console_handle() == NULL)
			seoul_logger::set_console_handle();


        switch (seoul_logger::get_log_level())
        {
            case LOG_GENERAL:
            {
                std::cout << "Initialized Logger with: LOG_GENERAL level" << Logger::LOG_MACRO::ENDL;
                break;
            }

			case LOG_ERROR:
			{
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_RED);
				std::cout << "LOG_ERROR";
				SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_WHITE);
				std::cout << " level" << Logger::LOG_MACRO::ENDL;
				break;
			}

            case LOG_SUCCESSFUL:
            {
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_GREEN);
				std::cout << "LOG_SUCCESSFUL";
				SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_WHITE);
				std::cout << " level" << Logger::LOG_MACRO::ENDL;
				break;
            }

            case LOG_WARNING:
            {
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_YELLOW);
				std::cout << "LOG_WARNING";
				SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_WHITE);
				std::cout << " level" << Logger::LOG_MACRO::ENDL;
				break;
            }

            default:
            {
                std::cout << "Initialized Logger with: Unknown level" << Logger::LOG_MACRO::ENDL;
                break;
            }
        }
    }

    return true;
}

bool seoul_logger::close_console_handle() const
{
	if (get_console_handle() == NULL || get_console_handle() == INVALID_HANDLE_VALUE)
		return false;

	else if (get_console_handle() != NULL && Console_already_There == true)
	{
		 CloseHandle(get_console_handle());
		 return true;
	}

	return false;
}

//Make sure to call this, at the end of your program
bool seoul_logger::Shutdown_Logger()
{
	FreeConsole();

	if (file_p)
		fclose(file_p);

	file_p = nullptr;

	if (get_console_handle() != nullptr && get_console_handle() != INVALID_HANDLE_VALUE)
		close_console_handle();

	if (log_file.is_open())
		log_file.close();

	already_down = true;


	return true;
}

//Prints something in the console
void seoul_logger::Print(const std::string &text)
{
	if (seoul_logger::get_log_mode() == seoul_logger::LOG_FILE_AND_CONSOLE)
	{
		switch (seoul_logger::get_log_level())
		{
		[[unlikely]] case seoul_logger::LOG_GENERAL:
		{
			if (seoul_logger::get_time_use() == true)
			{
				std::cout << "{" << seoul_logger::get_current_time() << "} ";
			}
			std::cout << "[";
			SetConsoleTextAttribute(get_console_handle(), 9);
			std::cout << "LOG_GENERAL";
			SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_WHITE);
			std::cout << "]" << " >> " << text << Logger::LOG_MACRO::ENDL;
			const auto temp_time = get_current_time();
			log_file << "{" + temp_time + "}" + "[" + "LOG_GENERAL" + "]" + " >> " + text << Logger::LOG_MACRO::ENDL;
			break;
		}

		[[likely]] case seoul_logger::LOG_ERROR:
		{
			if (seoul_logger::get_time_use() == true)
			{
				std::cout << "{" << seoul_logger::get_current_time() << "} ";
			}
			std::cout << "[";
			SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_RED);
			std::cout << "LOG_ERROR";
			SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_WHITE);
			std::cout << "]" << " >> " << text << Logger::LOG_MACRO::ENDL;
			const auto temp_time = get_current_time();
			log_file << "{" + temp_time + "}" + "[" + "LOG_ERROR" + "]" + " >> " + text << Logger::LOG_MACRO::ENDL;
			break;
		}

		[[likely]] case LOG_SUCCESSFUL:
		{
			if (seoul_logger::get_time_use() == true)
			{
				std::cout << "{" << seoul_logger::get_current_time() << "} ";
			}
			std::cout << "[";
			SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_GREEN);
			std::cout << "LOG_SUCCESSFUL";
			SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_WHITE);
			std::cout << "]" << " >> " << text << Logger::LOG_MACRO::ENDL;
			const auto temp_time = get_current_time();
			log_file << "{" + temp_time + "}" + "[" + "LOG_SUCCESSFUL" + "]" + " >> " + text << Logger::LOG_MACRO::ENDL;
			break;
		}

		case LOG_WARNING:
		{
			if (seoul_logger::get_time_use() == true)
			{
				std::cout << "{" << seoul_logger::get_current_time() << "} ";
			}
			std::cout << "[";
			SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_YELLOW);
			std::cout << "LOG_WARNING";
			SetConsoleTextAttribute(get_console_handle(), Logger::LOG_COLOR::COLOR_WHITE);
			std::cout << "]" << " >> " << text << Logger::LOG_MACRO::ENDL;
			const auto temp_time = get_current_time();
			log_file << "{" + temp_time + "}" + "[" + "LOG_WARNING" + "]" + " >> " + text << Logger::LOG_MACRO::ENDL;
			break;
		}

		default:
			break;

		}

	}

	else if (seoul_logger::get_log_mode() == LOG_CONSOLE)
	{
		[[likely]]
		switch (seoul_logger::get_log_level())
		{
		[[unlikely]] case LOG_GENERAL:
		{
			if (seoul_logger::get_time_use() == true)
			{
				std::cout << "{" << seoul_logger::get_current_time() << "} ";
			}
			std::cout << "[";
			SetConsoleTextAttribute(get_console_handle(), 9);
			std::cout << "LOG_GENERAL";
			SetConsoleTextAttribute(get_console_handle(), 15);
			std::cout << "]" << " >> " << text << Logger::LOG_MACRO::ENDL;
			break;
		}

		[[likely]] case LOG_SUCCESSFUL:
		{
			if (seoul_logger::get_time_use() == true)
			{
				std::cout << "{" << seoul_logger::get_current_time() << "} ";
			}
			std::cout << "[";
			SetConsoleTextAttribute(get_console_handle(), 10);
			std::cout << "LOG_SUCCESSFUL";
			SetConsoleTextAttribute(get_console_handle(), 15);
			std::cout << "]" << " >> " << text << Logger::LOG_MACRO::ENDL;
			break;
		}

		case LOG_WARNING:
		{
			if (seoul_logger::get_time_use() == true)
			{
				std::cout << "{" << seoul_logger::get_current_time() << "} ";
			}

			std::cout << "[";
			SetConsoleTextAttribute(get_console_handle(), 14);
			std::cout << "LOG_WARNING";
			SetConsoleTextAttribute(get_console_handle(), 15);
			std::cout << "]" << " >> " << text << Logger::LOG_MACRO::ENDL;
			break;
		}

		[[likely]] case LOG_ERROR:
		{
			if (seoul_logger::get_time_use() == true)
			{
				std::cout << "{" << seoul_logger::get_current_time() << "} ";
			}

			std::cout << "[";
			SetConsoleTextAttribute(get_console_handle(), 12);
			std::cout << "LOG_ERROR";
			SetConsoleTextAttribute(get_console_handle(), 15);
			std::cout << "]" << " >> " << text << Logger::LOG_MACRO::ENDL;
			break;
		}

		default:
			break;
		

		}

	}

	else if (seoul_logger::get_log_mode() == LOG_FILE)
{
    switch (get_log_level())
    {
       [[unlikely]]case LOG_GENERAL:
        {
            if (log_file.is_open())
            {
                const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_GENERAL" + "]" + " >> " + text << Logger::LOG_MACRO::ENDL;
                break;
            }
            break;
        }
        [[likely]]case LOG_ERROR:
        {
            if (log_file.is_open())
            {
               const  auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_ERROR" + "]" + " >> " + text << Logger::LOG_MACRO::ENDL;
                break;
            }
            break;
        }
        [[likely]]case LOG_SUCCESSFUL:
        {
            if (log_file.is_open())
            {
                const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_SUCCESSFUL" + "]" + " >> " + text << Logger::LOG_MACRO::ENDL;
                break;
            }
            break;
        }
        case LOG_WARNING:
        {
            if (log_file.is_open())
            {
                const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_WARNING" + "]" + " >> "+ text << Logger::LOG_MACRO::ENDL;
                break;
            }
            break;
        }
    }
}

	else
	{
		MessageBeep(MB_ICONERROR);
		MessageBoxA(nullptr, "Weird!", "test!", 0);
		return;
	}

}

std::string seoul_logger::get_exe_file_name()
{
	char buff[MAX_PATH];
	GetModuleFileNameA(NULL, buff, MAX_PATH);
	return std::string(buff);
}



bool seoul_logger::Create_Log_File(const std::string log_file_name, bool in_directory, std::string Location, std::string name_of_application)
{

	if (in_directory == true && log_file_name.empty() != true)
	{
		std::string log = get_exe_file_name();

		const auto string_check = log.find(name_of_application);

		if (string_check != std::string::npos)
		{
			log.erase(string_check, name_of_application.length());
		}

		auto end_var = log;
		end_var.append(log_file_name + ".txt");


		if (std::filesystem::exists(end_var))
			std::filesystem::remove(end_var);

		log_file.open(end_var);
		return true;
	}


	else if (in_directory == false && Location.empty() != true)
	{

		if (std::filesystem::exists(Location))
		{
			Location.append("\\");
			Location.append(log_file_name + ".txt");

			if (std::filesystem::exists(Location))
				std::filesystem::remove(Location);

			else
			{
				log_file.open(Location);
				return true;
			}


		}


	}

	else
	{
		Logger::helper::ShowMessageBox("Something went wrong", "Error Create_log_file!", true);
		return false;
	}

	return false;
}
