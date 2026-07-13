cmake_minimum_required(VERSION 3.16)

project(DemoVTK LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencia utilizada por algunos modulos de VTK.
find_package(nlohmann_json CONFIG REQUIRED)

# Modulos de VTK necesarios para mostrar el cono.
find_package(VTK REQUIRED COMPONENTS
    CommonCore
    CommonDataModel
    FiltersSources
    RenderingCore
    RenderingOpenGL2
    InteractionStyle
)

add_executable(vtk_demo vtk_demo.cpp)

target_link_libraries(vtk_demo PRIVATE
    ${VTK_LIBRARIES}
    nlohmann_json::nlohmann_json
)

vtk_module_autoinit(
    TARGETS vtk_demo
    MODULES ${VTK_LIBRARIES}
)