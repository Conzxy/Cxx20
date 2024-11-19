function (add_executable_11 TARGET)
    add_executable(${TARGET} ${ARGN})
    target_compile_features(${TARGET} PRIVATE cxx_std_11)
endfunction()

function (add_executable_20 TARGET)
    add_executable(${TARGET} ${ARGN})
    target_compile_features(${TARGET} PRIVATE cxx_std_20)
endfunction()

# To MSVC, this function is useless, it seems been 11 at least
function (add_executable_98 TARGET)
    add_executable(${TARGET} ${ARGN})
    set_target_properties(${TARGET} PROPERTIES CXX_STANDARD 98)
    set_target_properties(${TARGET} PROPERTIES CXX_STANDARD_REQUIRED YES)
    set_target_properties(${TARGET} PROPERTIES CXX_EXTENSIONS OFF)
endfunction()