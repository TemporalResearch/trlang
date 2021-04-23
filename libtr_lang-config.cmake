if (TARGET libtr_lang::libtr_lang)
    message("Target already exists")
    return()
endif()

add_library(libtr_lang::libtr_lang INTERFACE IMPORTED)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/include libtr_lang)

SET_TARGET_PROPERTIES(libtr_lang::libtr_lang PROPERTIES LINKED_LANGUAGE CXX)

target_include_directories(libtr_lang::libtr_lang
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(libtr_lang::libtr_lang
        INTERFACE trlang_src_module)

