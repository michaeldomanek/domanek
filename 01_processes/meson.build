project('01_processes', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

src = ['src/abc.cpp']

executable('XXX',
            sources : src,
            dependencies : thread_dep
           )

executable('charout',
            sources : ['src/charout.cpp'],
            dependencies : thread_dep
           )

