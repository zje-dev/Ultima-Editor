cmake_minimum_required(VERSION 3.16.3)

project(UltimaEditor)

file(GLOB cpp "../src/*.cpp")
file(GLOB cga "../src/cga/*.cpp")
file(GLOB ega "../src/ega/*.cpp")
file(GLOB t1k "../src/t1k/*.cpp")
file(GLOB run "../src/run/*.cpp")
file(GLOB gra "../src/graphic/*.cpp")
file(GLOB map "../src/map/*.cpp")
file(GLOB col "../src/color/*.cpp")

find_package(PkgConfig REQUIRED)

find_package(wxWidgets COMPONENTS net gl core base)
add_executable(ud ${ega} ${cga} ${run} ${gra} ${map} ${cpp} ${col} ${t1k})
if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
	target_link_libraries(ud ${wxWidgets_LIBRARIES})
endif()

add_compile_options(-lm)
add_compile_options(-Wwrite-strings)
add_compile_options(-fpermissive)
add_compile_options(-std=c++17)
