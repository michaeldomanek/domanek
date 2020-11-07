project('04_Sync2', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

inc_dir = include_directories(['include'])

src = ['src/main.cpp', 'src/work_queue.cpp']

executable('loadsim',
            sources : src,
            include_directories : inc_dir,
            dependencies : thread_dep,
           )
