project('08_daytime', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

inc_dir = include_directories(['include',                          
                              ])

# begin asio: https://think-async.com/Asio/
add_global_arguments('-I' + get_option('asio_include_dir'), language : 'cpp')
add_global_arguments('-DASIO_STANDALONE', language : 'cpp')
add_global_arguments('-DASIO_NO_DEPRECATED', language : 'cpp')
# end asio

# CLI11: https://github.com/CLIUtils/CLI11
add_global_arguments('-I' + get_option('cli11_include_dir'), language : 'cpp')

# spdlog: https://github.com/gabime/spdlog
add_global_arguments('-I' + get_option('spdlog_include_dir'), language : 'cpp')

executable('client',
            sources : ['src/daytime_client/main.cpp'],
            include_directories : 'include',
            dependencies : thread_dep,
           )

# executable('server',
#             sources : ['src/daytime_server'],
#             include_directories : inc_dir,
#             #dependencies : XXX_dep,
#            )
