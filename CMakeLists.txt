cmake_minimum_required(VERSION 3.10)


set(MINOR_VERSION "1" CACHE INTERNAL "Minor version")
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.${MINOR_VERSION}.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

# Добавляем подмодуль googletest
add_subdirectory(external/googletest EXCLUDE_FROM_ALL)

# Указываем, где искать собранные библиотеки gtest
set(GTEST_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/googletest/include")
set(GTEST_LIBRARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/external/googletest/build/lib")

# Создаем интерфейсную библиотеку для gtest
add_library(GTest::GTest INTERFACE IMPORTED)
target_include_directories(GTest::GTest INTERFACE ${GTEST_INCLUDE_DIRS})
target_link_directories(GTest::GTest INTERFACE ${GTEST_LIBRARY_DIR})
target_link_libraries(GTest::GTest INTERFACE gtest)

# Создаем интерфейсную библиотеку для gtest_main
add_library(GTest::Main INTERFACE IMPORTED)
target_include_directories(GTest::Main INTERFACE ${GTEST_INCLUDE_DIRS})
target_link_directories(GTest::Main INTERFACE ${GTEST_LIBRARY_DIR})
target_link_libraries(GTest::Main INTERFACE gtest_main)



add_executable(ip_filter_cli main.cpp)
add_library(ip_filter ip_filter.cpp)
add_executable(tests tests.cpp)

set_target_properties(ip_filter_cli ip_filter tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter PRIVATE "${CMAKE_BINARY_DIR}")

target_link_libraries(ip_filter_cli PRIVATE ip_filter)
target_link_libraries(tests PRIVATE GTest::Main ip_filter)

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE /W4)
    target_compile_options(ip_filter PRIVATE /W4)
    target_compile_options(tests PRIVATE /W4)
else ()
    target_compile_options(ip_filter_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(ip_filter PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Установка целевых файлов
install(TARGETS ip_filter_cli RUNTIME DESTINATION bin COMPONENT cli)
install(TARGETS ip_filter LIBRARY DESTINATION lib COMPONENT lib)

# Настройки CPack
set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_PACKAGE_DESCRIPTION "A simple hello world application")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
set(CPACK_GENERATOR "RPM;DEB")  # Укажите генераторы, которые вы хотите использовать

include(CPack)

# Включение тестирования
enable_testing()
add_test(tests tests)

include(GoogleTest)
gtest_discover_tests(tests)
