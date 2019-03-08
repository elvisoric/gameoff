project('Game', 'cpp', default_options:['cpp_std=c++17'])

incdir = include_directories(['include'])
glfw_dep = dependency('glfw3')

srcs = [
    'src/main.cpp',
    'src/window.cpp', 
    'src/glad.cpp', 
    'src/core/shader_program.cpp',
    'src/core/loader.cpp',
    'src/core/renderer.cpp']

entt_sp = subproject('entt')
entt_dep = entt_sp.get_variable('entt_dep')

patterns_sp = subproject('patterns')
patterns_dep = patterns_sp.get_variable('patterns_dep')

executable('Game', srcs, include_directories:incdir, dependencies:[entt_dep, glfw_dep, patterns_dep], link_args:['-ldl'])
