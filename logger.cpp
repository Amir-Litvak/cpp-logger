#include <iostream> //cerr
#include <time.h>   //for time_t
#include <memory>   //for std::shared_ptr

#include "logger.hpp"

namespace ilrd
{
    class Log : public Task
    {
    public:
        Log(std::string log, std::string path);
        void virtual operator()();

    private:
        std::string m_log;
        std::string m_path;
    };

    Log::Log(std::string log, std::string path) : m_log(log), m_path(path)
    {
        // empty
    }

    void Log::operator()()
    {
        std::ofstream m_file;
        m_file.open(m_path, std::fstream::in | std::fstream::app);
        m_file << m_log << std::endl;
        m_file.close();
    }

    Logger::Logger(const std::string &path) : m_path(path), m_tp(1)
    {
        m_tp.Run();
    }

    void Logger::SetPath(const std::string &path)
    {
        std::rename(m_path.c_str(), path.c_str());
        m_path = path;
    }

    void Logger::Log(const std::string &log)
    {
        time_t now = time(NULL);
        struct tm tstruct;
        char time[80];

        tstruct = *localtime(&now);
        strftime(time, sizeof(time), "%d-%m-%Y.%X: ", &tstruct);

        std::string timed_log = time + log;
        std::shared_ptr<Task> new_log(new Log(timed_log, m_path));

        m_tp.Add(new_log, MEDIUM);
    }
}
