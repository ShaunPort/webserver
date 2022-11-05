
include_directories(include)

aux_source_directory(epoller EPOLLER)

add_executable(webserver main.cpp ${EPOLLER})