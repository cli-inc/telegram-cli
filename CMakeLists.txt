cmake_minimum_required(VERSION 3.9)

project(telegram-cli VERSION 0.1.0 LANGUAGES CXX)

# create config.h
option(USE_JSON ON)
set(PACKAGE_NAME \"telegram-cli\")
set(PACKAGE_VERSION $VERSION)
set(PACKAGE_BUGREPORT \"https://github.com/cli-inc/telegram-cli/issues\")
set(USE_JSON ON)
configure_file(config.h.in config.h @ONLY)

#find_package(Td 1.3.0 REQUIRED)    # required for tdlib
find_library(readline telegram-cli)

add_executable(telegram-cli
    config.h
    main.cpp
    main.h
    options.h
    interface.cpp
    interface.h)

target_link_libraries(telegram-cli readline)
#target_link_libraries(telegram-cli PRIVATE Td::TdStatic)
set_property(TARGET telegram-cli PROPERTY CXX_STANDARD 14)


#install argument
install(TARGETS telegram-cli
        RUNTIME DESTINATION bin)
install(FILES LICENSE DESTINATION /usr/share/licenses/telegram-cli/LICENSE)