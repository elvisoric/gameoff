project('Game', 'cpp', default_options:['cpp_std=c++17'])

incdir = include_directories(['include'])
glfw_dep = dependency('glfw3')

srcs = ['src/main.cpp','src/window.cpp', 'src/glad.cpp', 'src/core/shader_program.cpp']

entt_sp = subproject('entt')
entt_dep = entt_sp.get_variable('entt_dep')

executable('Game', srcs, include_directories:incdir, dependencies:[entt_dep, glfw_dep])
