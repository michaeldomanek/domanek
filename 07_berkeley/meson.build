project('07_berkeley', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

inc_dir = include_directories(['include'],
                              get_option('cli11_include_dir')
                             )

src = ['src/main.cpp', 'src/clock.cpp']

executable('berkeley',
            sources : src,
            include_directories : inc_dir,
            dependencies : thread_dep,
           )

