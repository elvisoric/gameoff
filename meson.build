project('Game', 'cpp', default_options:['cpp_std=c++1z'])

incdir = include_directories(['include'])
srcs = ['src/main.cpp']

entt_sp = subproject('entt')
entt_dep = entt_sp.get_variable('entt_dep')


executable('Game', srcs, include_directories:incdir, dependencies:entt_dep)