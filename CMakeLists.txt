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
  src/${PROJECT_NAME}/utils.cpp
  src/${PROJECT_NAME}/client.cpp
  src/${PROJECT_NAME}/chat.cpp
  src/${PROJECT_NAME}/assistants.cpp
  src/${PROJECT_NAME}/threads.cpp
  src/${PROJECT_NAME}/messages.cpp
  src/${PROJECT_NAME}/runs.cpp
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

# samples
set(SAMPLE_NAMES
  chat
  chat_with_image_uri
  use_thread
)
foreach(sample_name IN LISTS SAMPLE_NAMES)
  add_executable(${PROJECT_NAME}_sample_${sample_name}
    src/${PROJECT_NAME}/samples/${sample_name}.cpp
  )
  target_link_libraries(${PROJECT_NAME}_sample_${sample_name}
    ${PROJECT_NAME}
  )
  install(
    TARGETS
      ${PROJECT_NAME}_sample_${sample_name}
    EXPORT ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
  )
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set_target_properties(${PROJECT_NAME}_sample_${sample_name}
      PROPERTIES INSTALL_RPATH "@executable_path/../lib")
  endif()
endforeach()

install(EXPORT ${PROJECT_NAME}
  FILE ${PROJECT_NAME}-config.cmake
  DESTINATION share/cmake/${PROJECT_NAME}/
  EXPORT_LINK_INTERFACE_LIBRARIES)

if (TEST)
  enable_testing()
  add_subdirectory(test)
endif()
