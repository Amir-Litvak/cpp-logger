#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string>  //std::string
#include <fstream> //std::fstream
#include <mutex>   //std::mutex

#include "singleton.hpp"
#include "thread_pool.hpp"

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace logger
{
    class Logger
    {
    public:
        void SetPath(const std::string &path);
        void Log(const std::string &log);

    private:
        Logger(const std::string &path = "./log.txt");
        friend class Singleton<Logger>;

        std::string m_path;
        ThreadPool m_tp;
    };
}


#endif //__LOGGER_HPP__