#include(${}/toolkit/toolkit.cmake)
#include(version/version.cmake)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    add_compile_options("/utf-8")
endif ()