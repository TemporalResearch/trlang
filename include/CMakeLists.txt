if (NOT TARGET trlang_src_module)
    add_library(trlang_src_module SHARED
            trlang.hpp
            trlang/ChunkGenerator.hpp
            trlang/Enum.hpp
            trlang/vector.hpp)

    SET_TARGET_PROPERTIES(trlang_src_module PROPERTIES LINKER_LANGUAGE CXX)
endif()