cmake_minimum_required(VERSION 3.20)
project(Alerta360 VERSION 1.0.0 LANGUAGES CXX)

option(ENABLE_SANITIZERS "Activar sanitizadores en GCC/Clang compatibles" OFF)

add_executable(alerta360
    main.cpp
    Estructuras.cpp
    GrafoCampus.cpp
    SistemaAlerta360.cpp
    Pruebas.cpp
    MapaVisual.cpp
    UbicacionesCampus.cpp
)
target_compile_features(alerta360 PRIVATE cxx_std_20)
set_target_properties(alerta360 PROPERTIES CXX_EXTENSIONS OFF)
if(WIN32)
    target_link_libraries(alerta360 PRIVATE shell32)
endif()

if(MSVC)
    target_compile_options(alerta360 PRIVATE /W4 /utf-8 /permissive-)
else()
    target_compile_options(alerta360 PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND NOT WIN32)
        target_compile_options(alerta360 PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(alerta360 PRIVATE -fsanitize=address,undefined)
    else()
        message(FATAL_ERROR "Los sanitizadores configurados requieren GCC/Clang en Linux/macOS.")
    endif()
endif()

enable_testing()
add_test(NAME pruebas_alerta360 COMMAND alerta360 --pruebas)
set_tests_properties(pruebas_alerta360 PROPERTIES TIMEOUT 60)
