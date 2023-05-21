#include "Logger.h"

inline Logger::LOG_LEVEL Logger::get_log_level() const
{
	return Logger::log_level;
}

Logger::LOG_LEVEL Logger::set_log_level(LOG_LEVEL new_log_level)
{
	return Logger::log_level = new_log_level;
}

inline Logger::LOG_MODE Logger::get_log_mode() const
{
	return Logger::log_mode;
}

Logger::LOG_MODE Logger::set_log_mode(LOG_MODE new_log_mode)
{
	return Logger::log_mode = new_log_mode;
}

std::string Logger::get_current_time()
{
	std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
    time_t t_time_t = std::chrono::system_clock::to_time_t(t);
    
    std::tm* local_time = std::localtime(&t_time_t);
    std::ostringstream oss;

	 oss << std::put_time(local_time, "%H:%M:%S");

	return oss.str();
}

HANDLE Logger::get_console_handle() const
{
	return Logger::console_handle;
}

HANDLE Logger::set_console_handle()
{
	return Logger::console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

//Make sure to call Create_log_file when u want to log into a file!
bool Logger::Init_Logger()
{
    if (Logger::init_log == false)
        Logger::init_log = true;

    if (Logger::get_log_mode() == LOG_CONSOLE || Logger::get_log_mode() == LOG_FILE_AND_CONSOLE)
    {
        AllocConsole();
        freopen_s(&file_p, "CONOUT$", "w", stdout);

    	if (Logger::get_console_handle() == NULL)
			Logger::set_console_handle();


        switch (Logger::get_log_level())
        {
            case LOG_ALL:
            {
                std::cout << "Initialized Logger with: LOG_ALL level" << ENDL;
                break;
            }

			case LOG_ERROR:
			{
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(get_console_handle(), COLOR_RED);
				std::cout << "LOG_ERROR";
				SetConsoleTextAttribute(get_console_handle(), COLOR_WHITE);
				std::cout << " level" << ENDL;
				break;
			}

            case LOG_SUCCESSFUL:
            {
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(get_console_handle(), COLOR_GREEN);
				std::cout << "LOG_SUCCESSFUL";
				SetConsoleTextAttribute(get_console_handle(), COLOR_WHITE);
				std::cout << " level" << ENDL;
				break;
            }

            case LOG_WARNING:
            {
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(get_console_handle(), COLOR_YELLOW);
				std::cout << "LOG_WARNING";
				SetConsoleTextAttribute(get_console_handle(), COLOR_WHITE);
				std::cout << " level" << ENDL;
				break;
            }

            default:
            {
                std::cout << "Initialized Logger with: Unknown level" << ENDL;
                break;
            }
        }
    }

    return true;
}

bool Logger::close_console_handle() const
{
	if (get_console_handle() == INVALID_HANDLE_VALUE || get_console_handle() == NULL)
		return true;

	else
	{
		 CloseHandle(get_console_handle());
		 return true;
	}
}

bool Logger::Shutdown_Logger()
{
	FreeConsole();

	if (file_p)
		fclose(file_p);

	file_p = nullptr;

	if (get_console_handle() != NULL || get_console_handle() != INVALID_HANDLE_VALUE)
		close_console_handle();

	if (log_file.is_open())
		log_file.close();

	return true;
}

void Logger::Print_log(std::string text)
{
	if (Logger::get_log_mode() == LOG_FILE_AND_CONSOLE)
	{
		switch (Logger::get_log_level())
		{
		[[unlikely]] case LOG_ALL:
			{	
				std::cout << "{" << Logger::get_current_time() << "} " << "[";
				SetConsoleTextAttribute(get_console_handle(), 9);
				std::cout << "LOG_ALL";
				SetConsoleTextAttribute(get_console_handle(), COLOR_WHITE);
				std::cout << "]" << " >> " << text << ENDL;
				const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_ALL" + "]" + " >> " + text << ENDL;
                break;
			}

		[[likely]] case  LOG_ERROR:
			{
				std::cout << "{" << Logger::get_current_time() << "} " << "[";
				SetConsoleTextAttribute(get_console_handle(), COLOR_RED);
				std::cout << "LOG_ERROR";
				SetConsoleTextAttribute(get_console_handle(), COLOR_WHITE);
				std::cout << "]" << " >> " << text << ENDL;
				const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_ERROR" + "]" + " >> " + text << ENDL;
                break;
			}

		[[likely]] case LOG_SUCCESSFUL:
			{
				std::cout << "{" << Logger::get_current_time() << "} " << "[";
				SetConsoleTextAttribute(get_console_handle(), COLOR_GREEN);
				std::cout << "LOG_SUCCESSFUL";
				SetConsoleTextAttribute(get_console_handle(), COLOR_WHITE);
				std::cout << "]" << " >> " << text << ENDL;
				const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_SUCCESSFUL" + "]" + " >> " + text << ENDL;
                break;
			}

		case LOG_WARNING:
			{
				std::cout << "{" << Logger::get_current_time() << "} " << "[";
				SetConsoleTextAttribute(get_console_handle(), COLOR_YELLOW);
				std::cout << "LOG_WARNING";
				SetConsoleTextAttribute(get_console_handle(), COLOR_WHITE);
				std::cout << "]" << " >> " << text << ENDL;
				const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_WARNING" + "]" + " >> " + text << ENDL;
                break;
			}

			default:
				break;

		}

	}

	else if (Logger::get_log_mode() == LOG_CONSOLE)
	{
		switch (Logger::get_log_level())
		{
		case LOG_ALL:
		{
			std::cout << "{" << Logger::get_current_time() << "} " << "[";
			SetConsoleTextAttribute(get_console_handle(), 9);
			std::cout << "LOG_ALL";
			SetConsoleTextAttribute(get_console_handle(), 15);
			std::cout << "]" << " >> " << text << ENDL;
			break;
		}

		case LOG_SUCCESSFUL:
		{
			std::cout << "{" << Logger::get_current_time() << "} " << "[";
			SetConsoleTextAttribute(get_console_handle(), 10);
			std::cout << "LOG_SUCCESSFUL";
			SetConsoleTextAttribute(get_console_handle(), 15);
			std::cout << "]" << " >> " << text << ENDL;
			break;
		}

		case LOG_WARNING:
		{
			std::cout << "{" << Logger::get_current_time() << "} " << "[";
			SetConsoleTextAttribute(get_console_handle(), 14);
			std::cout << "LOG_WARNING";
			SetConsoleTextAttribute(get_console_handle(), 15);
			std::cout << "]" << " >> " << text << ENDL;
			break;
		}

		[[likely]] case LOG_ERROR:
		{
			std::cout << "{" << Logger::get_current_time() << "} " << "[";
			SetConsoleTextAttribute(get_console_handle(), 12);
			std::cout << "LOG_ERROR";
			SetConsoleTextAttribute(get_console_handle(), 15);
			std::cout << "]" << " >> " << text << ENDL;
			break;
		}

		default:
			break;
		

		}

	}

	else if (Logger::get_log_mode() == LOG_FILE)
{
    switch (get_log_level())
    {
        case LOG_ALL:
        {
            if (log_file.is_open())
            {
                const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_ALL" + "]" + " >> " + text << ENDL;
                break;
            }
            break;
        }
        case LOG_ERROR:
        {
            if (log_file.is_open())
            {
               const  auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_ERROR" + "]" + " >> " + text << ENDL;
                break;
            }
            break;
        }
        case LOG_SUCCESSFUL:
        {
            if (log_file.is_open())
            {
                const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_SUCCESSFUL" + "]" + " >> " + text << ENDL;
                break;
            }
            break;
        }
        case LOG_WARNING:
        {
            if (log_file.is_open())
            {
                const auto temp_time = get_current_time();
                log_file << "{" + temp_time + "}" + "[" + "LOG_WARNING" + "]" + " >> "+ text << ENDL;
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

std::string Logger::get_exe_path()
{
	std::string f = get_exe_file_name();
	f.substr(0, f.find_last_of("\\/"));
	f.erase(f.end() - 19, f.end());
	return f;
}

std::string Logger::get_exe_file_name()
{
	char buff[MAX_PATH];
	GetModuleFileNameA(NULL, buff, MAX_PATH);
	return std::string(buff);
}

bool Logger::Create_Log_File(std::string log_file_name)
{
	std::string log = get_exe_path();
	log.append(log_file_name);

	if (std::filesystem::exists(log))
		std::filesystem::remove(log);

	log_file.open(log);
	return true;
}
