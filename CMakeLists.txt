cmake_minimum_required (VERSION 3.5)
project (poco-VladoClientTest)

find_package (Poco REQUIRED Net)

add_executable (clientTest main.cpp)
target_link_libraries (clientTest Poco::Net)
