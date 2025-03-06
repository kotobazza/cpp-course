```cmake
cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

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

# Остальная часть вашего CMakeLists.txt
configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld PRIVATE "${CMAKE_BINARY_DIR}")

target_link_libraries(helloworld_cli PRIVATE helloworld)
target_link_libraries(test_version PRIVATE GTest::Main helloworld)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(helloworld PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Установка целевых файлов
install(TARGETS helloworld_cli RUNTIME DESTINATION bin COMPONENT cli)
install(TARGETS helloworld LIBRARY DESTINATION lib COMPONENT lib)

# Настройки CPack
set(CPACK_PACKAGE_NAME "helloworld")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_PACKAGE_DESCRIPTION "A simple hello world application")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
set(CPACK_GENERATOR "RPM;DEB")  # Укажите генераторы, которые вы хотите использовать

include(CPack)

# Включение тестирования
enable_testing()
add_test(test_version test_version)

include(GoogleTest)
gtest_discover_tests(test_version)
```