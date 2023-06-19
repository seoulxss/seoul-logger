#include "Logger.h"

bool priv_logger::helper::ShowMessageBox(const char* Text, const char* Title, bool beep)
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


inline Cseoul_logger::LOG_LEVEL Cseoul_logger::get_log_level() const
{
	return this->log_level;
}

Cseoul_logger::LOG_LEVEL Cseoul_logger::set_log_level(const LOG_LEVEL new_log_level)
{
	return this->log_level = new_log_level;
}

inline Cseoul_logger::LOG_MODE Cseoul_logger::get_log_mode() const
{
	return this->log_mode;
}

Cseoul_logger::LOG_MODE Cseoul_logger::set_log_mode(const LOG_MODE new_log_mode)
{
	return this->log_mode = new_log_mode;
}

std::string Cseoul_logger::get_current_time()
{
	const std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
	const time_t t_time_t = std::chrono::system_clock::to_time_t(t);

	const std::tm* local_time = std::localtime(&t_time_t);
	std::ostringstream oss;

	oss << std::put_time(local_time, "%H:%M:%S");

	return oss.str();
}

bool Cseoul_logger::set_time_use(const bool val)
{
	return this->use_time = val;
}

bool Cseoul_logger::get_time_use() const
{
	return this->use_time;
}

HANDLE Cseoul_logger::get_console_handle() const
{
	return this->console_handle;
}

HANDLE Cseoul_logger::set_console_handle()
{
	return this->console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

//Make sure to call Create_log_file when u want to log into a file!
//This also gets called automatically, so no need to call it again.
bool Cseoul_logger::Init_Logger()
{
	if (Cseoul_logger::init_log == false)
		Cseoul_logger::init_log = true;

	else if (Cseoul_logger::init_log == true)
		return true;

	if (Cseoul_logger::get_log_mode() == LOG_CONSOLE || Cseoul_logger::get_log_mode() == LOG_FILE_AND_CONSOLE)
	{
		if (Cseoul_logger::set_console_handle() != nullptr)
			Console_already_There = true;

		if (Cseoul_logger::get_console_handle() == nullptr)
		{
			AllocConsole();
			freopen_s(&file_p, "CONOUT$", "w", stdout);
		}


		if (Cseoul_logger::get_console_handle() == NULL)
			Cseoul_logger::set_console_handle();


		switch (Cseoul_logger::get_log_level())
		{
		case LOG_LEVEL::LOG_GENERAL:
			{
				std::cout << "Initialized Logger with: LOG_GENERAL level" << priv_logger::LOG_MACRO__::ENDL;
				break;
			}

		case LOG_LEVEL::LOG_ERROR:
			{
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_RED);
				std::cout << "LOG_ERROR";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_WHITE);
				std::cout << " level" << priv_logger::LOG_MACRO__::ENDL;
				break;
			}

		case LOG_LEVEL::LOG_SUCCESSFUL:
			{
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_GREEN);
				std::cout << "LOG_SUCCESSFUL";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_WHITE);
				std::cout << " level" << priv_logger::LOG_MACRO__::ENDL;
				break;
			}

		case LOG_LEVEL::LOG_WARNING:
			{
				std::cout << "Initialized Logger with: ";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_YELLOW);
				std::cout << "LOG_WARNING";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_WHITE);
				std::cout << " level" << priv_logger::LOG_MACRO__::ENDL;
				break;
			}

		default:
			{
				std::cout << "Initialized Logger with: Unknown level" << priv_logger::LOG_MACRO__::ENDL;
				break;
			}
		}
	}

	return true;
}

bool Cseoul_logger::close_console_handle() const
{
	if (Cseoul_logger::get_console_handle() == NULL || Cseoul_logger::get_console_handle() == INVALID_HANDLE_VALUE)
		return false;

	else if (Cseoul_logger::get_console_handle() != NULL && this->Console_already_There == true)
	{
		CloseHandle(Cseoul_logger::get_console_handle());
		return true;
	}

	return false;
}

bool Cseoul_logger::Shutdown_Logger()
{
	if (CCounter::Oustanding_Objects() == 1)
		FreeConsole();

	if (file_p)
		fclose(file_p);

	file_p = nullptr;

	if (Cseoul_logger::get_console_handle() != nullptr && Cseoul_logger::get_console_handle() != INVALID_HANDLE_VALUE && CCounter::Oustanding_Objects() == 1)
		Cseoul_logger::close_console_handle();

	if (log_file.is_open())
		log_file.close();

	already_down = true;


	return true;
}

//Prints something in the console
void Cseoul_logger::Print(const std::string& text)
{
	if (Cseoul_logger::get_log_mode() == Cseoul_logger::LOG_FILE_AND_CONSOLE)
	{
		//Check if file is open etc..


		switch (Cseoul_logger::get_log_level())
		{
			[[unlikely]] case Cseoul_logger::LOG_LEVEL::LOG_GENERAL:
			{
				if (Cseoul_logger::get_time_use() == true)
				{
					std::cout << "{" << Cseoul_logger::get_current_time() << "} ";
				}
				std::cout << "[";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 9);
				std::cout << "LOG_GENERAL";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_WHITE);
				std::cout << "]" << " >> " << text << priv_logger::LOG_MACRO__::ENDL;
				const auto temp_time = get_current_time();
				log_file << "{" + temp_time + "}" + "[" + "LOG_GENERAL" + "]" + " >> " + text <<
					priv_logger::LOG_MACRO__::ENDL;
				break;

				//Clsoe the file again
			}

			[[likely]] case Cseoul_logger::LOG_LEVEL::LOG_ERROR:
			{
				if (Cseoul_logger::get_time_use() == true)
				{
					std::cout << "{" << Cseoul_logger::get_current_time() << "} ";
				}
				std::cout << "[";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_RED);
				std::cout << "LOG_ERROR";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_WHITE);
				std::cout << "]" << " >> " << text << priv_logger::LOG_MACRO__::ENDL;
				const auto temp_time = Cseoul_logger::get_current_time();
				log_file << "{" + temp_time + "}" + "[" + "LOG_ERROR" + "]" + " >> " + text <<
					priv_logger::LOG_MACRO__::ENDL;
				break;
			}

			[[likely]] case LOG_LEVEL::LOG_SUCCESSFUL:
			{
				if (Cseoul_logger::get_time_use() == true)
				{
					std::cout << "{" << Cseoul_logger::get_current_time() << "} ";
				}
				std::cout << "[";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_GREEN);
				std::cout << "LOG_SUCCESSFUL";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_WHITE);
				std::cout << "]" << " >> " << text << priv_logger::LOG_MACRO__::ENDL;
				const auto temp_time = Cseoul_logger::get_current_time();
				log_file << "{" + temp_time + "}" + "[" + "LOG_SUCCESSFUL" + "]" + " >> " + text <<
					priv_logger::LOG_MACRO__::ENDL;
				break;
			}

		case LOG_LEVEL::LOG_WARNING:
			{
				if (Cseoul_logger::get_time_use() == true)
				{
					std::cout << "{" << Cseoul_logger::get_current_time() << "} ";
				}
				std::cout << "[";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_YELLOW);
				std::cout << "LOG_WARNING";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), priv_logger::LOG_COLOR__::COLOR_WHITE);
				std::cout << "]" << " >> " << text << priv_logger::LOG_MACRO__::ENDL;
				const auto temp_time = Cseoul_logger::get_current_time();
				log_file << "{" + temp_time + "}" + "[" + "LOG_WARNING" + "]" + " >> " + text <<
					priv_logger::LOG_MACRO__::ENDL;
				break;
			}

		default:
			break;
		}
	}

	else if (Cseoul_logger::get_log_mode() == LOG_CONSOLE)
	{
		[[likely]]
		switch (Cseoul_logger::get_log_level())
		{
			[[unlikely]] case LOG_LEVEL::LOG_GENERAL:
			{
				if (Cseoul_logger::get_time_use() == true)
				{
					std::cout << "{" << Cseoul_logger::get_current_time() << "} ";
				}
				std::cout << "[";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 9);
				std::cout << "LOG_GENERAL";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 15);
				std::cout << "]" << " >> " << text << priv_logger::LOG_MACRO__::ENDL;
				break;
			}

			[[likely]] case LOG_LEVEL::LOG_SUCCESSFUL:
			{
				if (Cseoul_logger::get_time_use() == true)
				{
					std::cout << "{" << Cseoul_logger::get_current_time() << "} ";
				}
				std::cout << "[";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 10);
				std::cout << "LOG_SUCCESSFUL";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 15);
				std::cout << "]" << " >> " << text << priv_logger::LOG_MACRO__::ENDL;
				break;
			}

		case LOG_LEVEL::LOG_WARNING:
			{
				if (Cseoul_logger::get_time_use() == true)
				{
					std::cout << "{" << Cseoul_logger::get_current_time() << "} ";
				}

				std::cout << "[";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 14);
				std::cout << "LOG_WARNING";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 15);
				std::cout << "]" << " >> " << text << priv_logger::LOG_MACRO__::ENDL;
				break;
			}

			[[likely]] case LOG_LEVEL::LOG_ERROR:
			{
				if (Cseoul_logger::get_time_use() == true)
				{
					std::cout << "{" << Cseoul_logger::get_current_time() << "} ";
				}

				std::cout << "[";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 12);
				std::cout << "LOG_ERROR";
				SetConsoleTextAttribute(Cseoul_logger::get_console_handle(), 15);
				std::cout << "]" << " >> " << text << priv_logger::LOG_MACRO__::ENDL;
				break;
			}

		default:
			break;
		}
	}

	else if (Cseoul_logger::get_log_mode() == LOG_FILE)
	{
		switch (get_log_level())
		{
			[[unlikely]]case LOG_LEVEL::LOG_GENERAL:
			{
				if (log_file.is_open())
				{
					const auto temp_time = Cseoul_logger::get_current_time();
					log_file << "{" + temp_time + "}" + "[" + "LOG_GENERAL" + "]" + " >> " + text <<
						priv_logger::LOG_MACRO__::ENDL;
					break;
				}
				break;
			}
			[[likely]]case LOG_LEVEL::LOG_ERROR:
			{
				if (log_file.is_open())
				{
					const auto temp_time = Cseoul_logger::get_current_time();
					log_file << "{" + temp_time + "}" + "[" + "LOG_ERROR" + "]" + " >> " + text <<
						priv_logger::LOG_MACRO__::ENDL;
					break;
				}
				break;
			}
			[[likely]]case LOG_LEVEL::LOG_SUCCESSFUL:
			{
				if (log_file.is_open())
				{
					const auto temp_time = Cseoul_logger::get_current_time();
					log_file << "{" + temp_time + "}" + "[" + "LOG_SUCCESSFUL" + "]" + " >> " + text <<
						priv_logger::LOG_MACRO__::ENDL;
					break;
				}
				break;
			}
		case LOG_LEVEL::LOG_WARNING:
			{
				if (log_file.is_open())
				{
					const auto temp_time = Cseoul_logger::get_current_time();
					log_file << "{" + temp_time + "}" + "[" + "LOG_WARNING" + "]" + " >> " + text <<
						priv_logger::LOG_MACRO__::ENDL;
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

std::string Cseoul_logger::get_exe_file_name()
{
	char buff[MAX_PATH];
	GetModuleFileNameA(nullptr, buff, MAX_PATH);
	return {buff};
}

bool Cseoul_logger::Create_Log_File(const std::string& log_file_name, bool in_directory, std::string Location,
                                    const std::string& name_of_application)
{
	if (in_directory == true && log_file_name.empty() != true)
	{
		std::string log = Cseoul_logger::get_exe_file_name();

		const auto string_check = log.find(name_of_application);

		if (string_check != std::string::npos)
		{
			log.erase(string_check, name_of_application.length());
		}

		//auto end_var = log;
		log.append(log_file_name + ".txt");


		if (std::filesystem::exists(log))
			std::filesystem::remove(log);

		log_file.open(log);
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


			Cseoul_logger::log_file_location = Location;
			Cseoul_logger::log_file.open(Location);
			return true;
		}
	}

	else
	[[unlikely]]         
	{
		priv_logger::helper::ShowMessageBox("Something went wrong", "Error Create_log_file!", true);
		return false;
	}

	return false;
}
