cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_C_STANDARD 11)

#add_compile_options(-Wall -Wextra -Wpedantic)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -D_GNU_SOURCE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -pedantic-errors -lm")

# Include and linking libs
include_directories(${CMAKE_SOURCE_DIR}/general/include)
link_directories(${CMAKE_SOURCE_DIR}/general/lib)

if (WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/windows/include)
    link_directories(${CMAKE_SOURCE_DIR}/windows/lib)
    project(gopherWin C)
    add_executable(gopherWin main.c general/lib/utils/utils.c general/include/utils.h general/lib/io/config_file.c general/include/config_file.h general/include/portables.h general/include/definitions.h general/lib/io/files_interaction.c general/include/files_interaction.h general/lib/gopher/protocol.c general/include/protocol.h windows/lib/socket/windows_socket.c windows/include/windows_socket.h windows/lib/thead/winThread.c windows/include/winThread.h windows/lib/io/windows_file_interactions.c windows/include/windows_file_interactions.h windows/lib/protocol/windows_protocol.c windows/include/windows_protocol.h general/lib/socket/socket.c general/include/socket.h windows/lib/memory_mapping/windows_memory_mapping.c windows/include/windows_memory_mapping.h windows/lib/events/windows_events.c windows/include/windows_events.h windows/lib/pipe/windows_pipe.c windows/include/windows_pipe.h windows/lib/utils/windows_utils.c windows/include/windows_utils.h)
    target_link_libraries(gopherWin ws2_32)
endif (WIN32)


if (WIN32)
    project(gopherWinPipeProcess C)
    add_executable(gopherWinPipeProcess main2.c general/include/definitions.h windows/lib/utils/windows_utils.c windows/include/windows_utils.h)
endif (WIN32)
if (WIN32)
    project(gopherWinHandleRequestProcess C)
    add_executable(gopherWinHandleRequestProcess main_HandleRequest.c  general/lib/utils/utils.c general/include/utils.h general/lib/io/config_file.c general/include/config_file.h general/include/portables.h general/include/definitions.h general/lib/io/files_interaction.c general/include/files_interaction.h general/lib/gopher/protocol.c general/include/protocol.h windows/lib/socket/windows_socket.c windows/include/windows_socket.h windows/lib/thead/winThread.c windows/include/winThread.h windows/lib/io/windows_file_interactions.c windows/include/windows_file_interactions.h windows/lib/protocol/windows_protocol.c windows/include/windows_protocol.h general/lib/socket/socket.c general/include/socket.h windows/lib/memory_mapping/windows_memory_mapping.c windows/include/windows_memory_mapping.h windows/lib/events/windows_events.c windows/include/windows_events.h windows/lib/pipe/windows_pipe.c windows/include/windows_pipe.h windows/lib/utils/windows_utils.c windows/include/windows_utils.h)
    #add_executable(gopherWinHandleRequestProcess  main_HandleRequest.c general/include/definitions.h)
    target_link_libraries(gopherWinHandleRequestProcess ws2_32)
endif (WIN32)


if (UNIX)
    include_directories(${CMAKE_SOURCE_DIR}/linux/include)
    link_directories(${CMAKE_SOURCE_DIR}/linux/lib)
    project(gopherLinux C)
    add_executable(gopherLinux main.c general/lib/utils/utils.c general/include/utils.h general/lib/io/config_file.c general/include/config_file.h linux/lib/utils/linux_portable_lib.c linux/include/linux_portable_lib.h linux/lib/utils/utils.c linux/include/utils.h general/lib/portable/portables.c general/include/portables.h general/include/definitions.h general/lib/io/files_interaction.c general/include/files_interaction.h general/lib/gopher/protocol.c general/include/protocol.h linux/lib/io/linux_files_interaction.c linux/include/linux_files_interaction.h general/include/ut_dict.h linux/lib/memory_mapping/linux_memory_mapping.c linux/include/linux_memory_mapping.h linux/lib/thread/linux_thread.c linux/include/linux_socket.h linux/lib/socket/linux_socket.c linux/include/linux_thread.h linux/lib/process/linux_process.c linux/include/linux_process.h linux/lib/protocol/linux_protocol.c linux/include/linux_protocol.h general/lib/socket/socket.c general/include/socket.h general/lib/memory_mapping/memory_mapping.c general/include/memory_mapping.h linux/lib/signals/linux_signals.c linux/include/linux_signals.h general/lib/linux_pipe.c general/include/linux_pipe.h)
    target_link_libraries(gopherLinux pthread -lrt)
endif (UNIX)
