add_executable(trl_tests src/test_runner.cpp
        src/OptionalTests.cpp
        src/ScopedTimerTests.cpp)

find_package(libautotest REQUIRED)

target_link_libraries(trl_tests
        PRIVATE libtr_lang::libtr_lang
        PRIVATE libautotest::libautotest
        )