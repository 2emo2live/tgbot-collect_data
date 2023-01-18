cmake_minimum_required(VERSION 3.11)

project(tgbot)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(doxyfile_in ${CMAKE_SOURCE_DIR})

	configure_file(Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	add_custom_target(docs 
	${DOXYGEN_EXECUTABLE}
	${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	COMMENT "Generating API documentation with Doxygen"
	VERBATIM
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

add_library (image_storage image_storage.h image_storage.cpp)
add_library (leaderboard leaderboard.h leaderboard.cpp)
add_executable(bot tgbot.cpp)

target_link_libraries(bot leaderboard image_storage ${VCPKG_INSTALLED_DIR}/x64-windows/lib/TgBot.lib ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})

#install(DIRECTORY ${VCPKG_INSTALLED_DIR}/x64-windows/bin DESTINATION tgbot)
#install(TARGETS bot DESTINATION tgbot/bin)
install(DIRECTORY ${tgbot_BINARY_DIR}/Release/ DESTINATION tgbot/bin)
install(TARGETS image_storage leaderboard DESTINATION tgbot/lib)
install(DIRECTORY DESTINATION tgbot/images)
install(DIRECTORY ${tgbot_SOURCE_DIR}/examples DESTINATION tgbot)
