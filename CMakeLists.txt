cmake_minimum_required(VERSION 3.10)

project(chatgpt_client_cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

set(cpprestsdk_LIBRARIES cpprestsdk::cpprest)

include_directories(
  include
)

add_library(${PROJECT_NAME} SHARED
  src/${PROJECT_NAME}/chat.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${cpprestsdk_LIBRARIES}
  ${OPENSSL_LIBRARIES}  # to avoid linker error
)
install(
  TARGETS
    ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY include/
  DESTINATION include)

if (TEST)
  enable_testing()
  add_subdirectory(test)
endif()
