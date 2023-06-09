cmake_minimum_required(VERSION 3.24)
project(swarm_engine C)

set(CMAKE_C_STANDARD 11)

add_executable(swarm_engine main.c)


target_include_directories(swarm_engine PRIVATE src/particle_adapter src/ant, src/simulation)

add_library(physics_lib STATIC
        libraries/physics/vector/vector2.c
        libraries/physics/particles/particle.c
        libraries/physics/aabb/aabb.c
        )
target_include_directories(physics_lib PUBLIC include/physics)
target_link_libraries(swarm_engine PUBLIC physics_lib)

add_library(src_lib STATIC
        src/particle_adapter/gl_particle_adapter.c
        src/simulation/simulation.c
        src/ant/ant.c
        )
target_include_directories(src_lib PUBLIC src/)
# Add src lib to swarm
target_link_libraries(swarm_engine PUBLIC src_lib)

# Add physics lib to src
target_link_libraries(src_lib PUBLIC physics_lib)


add_library(glad_lib STATIC libraries/glad.c)
target_include_directories(glad_lib PUBLIC include/glad/)
target_link_libraries(swarm_engine PRIVATE glad_lib)

target_link_libraries(swarm_engine PUBLIC GL dl glfw -lm ${LIBS})