project('08_daytime', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

# thread_dep = dependency('threads')

inc_dir = include_directories(['include',
#                               get_option('cli11_include_dir'),
#                               get_option('spdlog_include_dir'),
#                               get_option('json_include_dir'),
#                               get_option('asio_include_dir')                               
                              ])

# spdlog: https://github.com/gabime/spdlog
add_global_arguments('-I' + get_option('spdlog_include_dir'), language : 'cpp')

executable('daytime',
            sources : ['src/main.cpp'],
            include_directories : inc_dir,
            #dependencies : XXX_dep,
           )

# executable('client',
#             sources : ['src/daytime_client/'],
#             include_directories : inc_dir,
#             #dependencies : XXX_dep,
#            )

# executable('server',
#             sources : ['src/daytime_server'],
#             include_directories : inc_dir,
#             #dependencies : XXX_dep,
#            )
