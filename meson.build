project('Lit', 'cpp', default_options : ['cpp_std=c++14'])

#check if the build is initiated through luarocks
bLuaRocks = get_option('lr_install_lib_dir') != '' and get_option('lr_install_lua_dir') != ''

if bLuaRocks
    message('Building through luarocks')
endif

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
    'Lit/Libs',
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

# empty array will trigger platform default
nameSuffix = []
namePrefix = []
installDir = []
if host_machine.system() == 'darwin' and bLuaRocks
    nameSuffix = 'so'
    namePrefix = ''
    installDir = get_option('lr_install_lib_dir')
endif

lit = shared_library('Lit', 
    litSrc, 
    dependencies: litDeps, 
    include_directories : incDirs,
    name_prefix: namePrefix, 
    name_suffix: nameSuffix,
    install_dir: installDir,
    install: true)

litDep = declare_dependency(link_with : lit, 
    dependencies: litDeps, 
    include_directories: incDirs)

#@TODO: install the lua files that are part of lit
