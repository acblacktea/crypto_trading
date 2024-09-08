cmake_minimum_required(VERSION 3.26)
project(crypto_trading)

set(CMAKE_CXX_STANDARD 23)

add_executable(crypto_trading src/main.cpp
        src/exchanges/binance/client.h
        src/exchanges/binance/client.cpp
        src/trading_engine/trading_engine.cpp
        src/trading_engine/trading_engine.h)
