#pragma once
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/async.h" //support for async logging.
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
#include "spdlog/cfg/env.h"

static std::shared_ptr<spdlog::logger> web_logger_ptr;

static const std::shared_ptr<spdlog::logger>& web_logger()
{    
    if(web_logger_ptr)
        return web_logger_ptr; 
    else
    {       
        spdlog::sink_ptr console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::debug);

        spdlog::sink_ptr file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("/home/logs/web.log", true);
        file_sink->set_level(spdlog::level::debug);

        spdlog::sinks_init_list sink_list = { file_sink, console_sink }; 
        
        spdlog::logger logger("web_request", sink_list.begin(), sink_list.end());

        logger.set_level(spdlog::level::debug);

        web_logger_ptr = std::make_shared<spdlog::logger>(logger);           
       
        return web_logger_ptr; 
    }
           
}








//auto web_logger_ptr = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "/home/logs/web.log");

