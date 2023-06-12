#pragma once

#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/mysql.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/system/system_error.hpp>
#include <string>

class SQLHandler{
    boost::asio::io_context ctx;    
};