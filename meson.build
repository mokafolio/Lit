project('Lit', 'cpp', default_options : ['cpp_std=c++14'])

#remove this rather bogus warning
add_global_arguments('-Wno-missing-braces', language: 'cpp')

litInc = [
    'Lit/Lit.hpp'
]
install_headers(litInc, subdir: 'Lit')

litLibInc = [
    'Lit/Libs/stb_image.h',
    'Lit/Libs/stb_image_write.h'
]
install_headers(litLibInc, subdir: 'Lit/Libs')

litSrc = [
    'Lit/Lit.cpp'
]

incDirs = include_directories(
    '.', 
    'subprojects/Crunch', 
    'subprojects/CrunchLuaSol', 
    'subprojects/Luke',
    'subprojects/LukeLuaSol',
    'subprojects/Paper2',
    'subprojects/PaperLuaSol',
    'subprojects/Stick')

litDeps = [
    dependency('threads'),
    subproject('Stick').get_variable('stickDep'),
    subproject('Luke').get_variable('lukeDep'),
    subproject('Paper2').get_variable('paperDep'),
    dependency('lua', version: '>=5.3')
]

lit = shared_library('Lit', litSrc, dependencies: litDeps, include_directories : incDirs, install: true)
