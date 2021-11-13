add_executable(trl_tests
        src/OptionalTests.cpp
        src/ScopedTimerTests.cpp src/main.cpp
        src/hfn/FunctorTests.cpp
        )

find_package(libautotest REQUIRED)

target_link_libraries(trl_tests
        PRIVATE libtr_lang::libtr_lang
        PRIVATE libautotest::libautotest
        PRIVATE Catch2::Catch2
        )