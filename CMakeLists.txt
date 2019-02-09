cmake_minimum_required(VERSION 3.9)

project(telegram-cli VERSION 0.1.0 LANGUAGES CXX)

# create config.h
option(USE_JSON ON)
set(PACKAGE_NAME \"telegram-cli\")
set(PACKAGE_VERSION $VERSION)
set(PACKAGE_BUGREPORT \"https://github.com/cli-inc/telegram-cli/issues\")
set(USE_JSON OFF)
configure_file(config.h.in config.h @ONLY)

#find_package(Td 1.3.0 REQUIRED)    # required for tdlib

add_executable(telegram-cli
    main.cpp
    config.h)
#target_link_libraries(telegram-cli PRIVATE Td::TdStatic)
set_property(TARGET telegram-cli PROPERTY CXX_STANDARD 14)
