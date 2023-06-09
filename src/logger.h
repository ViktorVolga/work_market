#pragma once
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/async.h" //support for async logging.
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

static spdlog::sink_ptr console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
static spdlog::sink_ptr file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("/home/logs/web.log", true);
static spdlog::sinks_init_list sink_list = { file_sink, console_sink };
static const std::shared_ptr<spdlog::logger> web_logger_ptr = std::make_shared<spdlog::logger>("web_request", sink_list.begin(), sink_list.end());


static const std::shared_ptr<spdlog::logger>& web_logger()
{    
    return web_logger_ptr;    
}








//auto web_logger_ptr = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "/home/logs/web.log");

