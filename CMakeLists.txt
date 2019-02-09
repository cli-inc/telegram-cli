cmake_minimum_required(VERSION 3.9)

project(telegram-cli VERSION 0.1.0 LANGUAGES CXX)

#find_package(Td 1.3.0 REQUIRED)    # required for tdlib

add_executable(telegram-cli main.cpp)
#target_link_libraries(telegram-cli PRIVATE Td::TdStatic)
set_property(TARGET telegram-cli PROPERTY CXX_STANDARD 14)
