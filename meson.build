project('chess', 'cpp',
    default_options : ['cpp_std=c++20', 'default_library=static']
)

src = [
    'Chess/src/BoardEngine.cpp',
    'Chess/src/BoardInterface.cpp',
    'Chess/src/BoardRenderer.cpp',
    'Chess/src/Game.cpp',
    'Chess/src/Main.cpp',
    'Chess/src/Piece.cpp',
    'Chess/src/Utils.cpp'
]

sfml = subproject('sfml')

executable('chess', src, dependencies: [sfml.get_variable('sfml_dep')])