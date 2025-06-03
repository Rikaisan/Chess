project('chess', 'cpp',
    default_options : ['cpp_std=c++20', 'default_library=static']
)

src = [
    'src/BoardEngine.cpp',
    'src/BoardInterface.cpp',
    'src/BoardRenderer.cpp',
    'src/Game.cpp',
    'src/Main.cpp',
    'src/Piece.cpp',
    'src/Utils.cpp'
]

if host_machine.system() == 'windows'
    windows = import('windows')
    windows_resources = windows.compile_resources('Chess.rc')
    src += windows_resources
endif

sfml = subproject('sfml')

executable('chess', src, dependencies: [sfml.get_variable('sfml_dep')])