project('Lit', 'cpp', default_options : ['cpp_std=c++14'])

#check if the build is initiated through luarocks
bLuaRocks = get_option('lr_install_lib_dir') != '' and get_option('lr_install_lua_dir') != ''

if bLuaRocks
    message('Building through luarocks')
endif

#remove this rather bogus warning
add_global_arguments('-Wno-missing-braces', language: 'cpp')

litInc = [
    'LitCore/LitCore.hpp'
]
install_headers(litInc, subdir: 'LitCore')

litLibInc = [
    'LitCore/Libs/stb_image.h',
    'LitCore/Libs/stb_image_write.h'
]
install_headers(litLibInc, subdir: 'LitCore/Libs')

litSrc = [
    'LitCore/LitCore.cpp'
]

incDirs = include_directories(
    '.', 
    'LitCore/Libs')

# meseon dependency function to find lua is not very consistent accross platforms yet, so
# we need to do a lot of manual lifting for now
if host_machine.system() == 'linux'
    luaDep = dependency('lua', version: '>=5.3', required: false)
    if not luaDep.found()
        luaDep = dependency('lua5.3', required: false)
        if not luaDep.found()
            luaDep = dependency('lua-5.3', required: false)
            if not luaDep.found()
                # this is our last chance, so we require this to succeed
                luaDep = dependency('lua53')
            endif
        endif
    endif
else
    #this will work on osx...so nothing else to do
    luaDep = dependency('lua', version: '>=5.3')
endif


litDeps = [
    dependency('threads'),
    subproject('Stick').get_variable('stickDep'),
    subproject('Luke').get_variable('lukeDep'),
    subproject('Paper2').get_variable('paperDep'),
    luaDep
]

luaInstallDir = 'LuaScripts'

# meson does not provide a good mechanism to pick default arguments for now
# so this is somewhat of a clumsy if else mess to invoke shared_library with
# the correct parameters.
if bLuaRocks
        
    #empty arry triggers default...
    nameSuffix = []
    namePrefix = 'lib' #for windows this will most likely have to be different
    # lets hope meson provides a better way for defaults once we get to that!!!!
    # I.e. this: https://github.com/mesonbuild/meson/pull/3820

    #conform to the expected lua shared lib naming conventions
    if host_machine.system() == 'darwin' 
        nameSuffix = 'so'
        namePrefix = ''
    endif
    installDir = get_option('lr_install_lib_dir')
    # luaInstallDir = join_paths(get_option('lr_install_lua_dir'), 'Lit')
    luaInstallDir = get_option('lr_install_lua_dir')

    lit = shared_library('LitCore', 
        litSrc, 
        dependencies: litDeps, 
        include_directories : incDirs,
        name_prefix: namePrefix, 
        name_suffix: nameSuffix,
        install_dir: installDir,
        install: true)
    install_subdir('LuaScripts', install_dir : luaInstallDir, strip_directory: true)
else
    lit = shared_library('LitCore',
        litSrc, 
        dependencies: litDeps, 
        include_directories : incDirs,
        install: true) 
endif

litDep = declare_dependency(link_with : lit, 
    dependencies: litDeps, 
    include_directories: incDirs)


