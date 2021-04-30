if (NOT TARGET trlang_src_module)
    add_library(trlang_src_module SHARED
            trlang.hpp
            trlang/ChunkGenerator.hpp
            trlang/Enum.hpp
            trlang/vector.hpp ../src/trlang/Curl.cpp trlang/Curl.hpp trlang/json.hpp ../src/trlang/json.cpp)

    target_include_directories(trlang_src_module
            PUBLIC ./)
    target_link_libraries(trlang_src_module
            PRIVATE curl
    )

    SET_TARGET_PROPERTIES(trlang_src_module PROPERTIES LINKER_LANGUAGE CXX)
endif()