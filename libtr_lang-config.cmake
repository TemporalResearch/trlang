if (TARGET libtr_lang::libtr_lang)
    return()
endif()

add_library(libtr_lang::libtr_lang INTERFACE IMPORTED)
target_include_directories(libtr_lang::libtr_lang
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

