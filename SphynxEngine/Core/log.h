//
// Created by andre on 23.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_LOG_H
#define CHUBBYSPHYNXENGINE_LOG_H

// External
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// STD
#include <string>
#include <memory>


namespace Sphynx {

    class Log {
    private:
        static std::shared_ptr<spdlog::logger> sm_coreLogger;
        static std::shared_ptr<spdlog::logger> sm_clientLogger;

    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return sm_coreLogger; }
        inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return sm_clientLogger;}
    };
}


#ifdef SPHYNX_DEBUG
#define SE_CORE_TRACE(...) Sphynx::Log::getCoreLogger()->trace(__VA_ARGS__);
#define SE_CORE_INFO(...) Sphynx::Log::getCoreLogger()->info(__VA_ARGS__);
#define SE_CORE_WARN(...) Sphynx::Log::getCoreLogger()->warn(__VA_ARGS__);
#define SE_CORE_ERROR(...) Sphynx::Log::getCoreLogger()->error(__VA_ARGS__);
#define SE_CORE_CRITICAL(...) Sphynx::Log::getCoreLogger()->critical(__VA_ARGS__);

#define SE_TRACE(...) Sphynx::Log::getClientLogger()->trace(__VA_ARGS__);
#define SE_INFO(...) Sphynx::Log::getClientLogger()->info(__VA_ARGS__);
#define SE_WARN(...) Sphynx::Log::getClientLogger()->warn(__VA_ARGS__);
#define SE_ERROR(...) Sphynx::Log::getClientLogger()->error(__VA_ARGS__);
#define SE_CRITICAL(...) Sphynx::Log::getClientLogger()->critical(__VA_ARGS__);

#else // Release

#define SE_CORE_TRACE(...);
#define SE_CORE_INFO(...);
#define SE_CORE_WARN(...);
#define SE_CORE_ERROR(...);
#define SE_CORE_CRITICAL(...);

#define SE_TRACE(...);
#define SE_INFO(...);
#define SE_WARN(...);
#define SE_ERROR(...);
#define SE_CRITICAL(...);


#endif


#endif //CHUBBYSPHYNXENGINE_LOG_H
