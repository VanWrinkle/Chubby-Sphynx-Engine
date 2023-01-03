/**
 *
 */

// Sphynx Engine
#include <log.h>

// STD
#include <memory>

namespace Sphynx {
    std::shared_ptr<spdlog::logger> Log::sm_coreLogger;
    std::shared_ptr<spdlog::logger> Log::sm_clientLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n %v%$");
        sm_coreLogger = spdlog::stdout_color_mt("[SPHYNX CORE]");
        sm_coreLogger->set_level(spdlog::level::trace);
        sm_clientLogger = spdlog::stdout_color_mt("[Client]");
        sm_clientLogger->set_level(spdlog::level::trace);
    }
}