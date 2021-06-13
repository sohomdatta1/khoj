cmake_minimum_required(VERSION 3.13)
project(khoj)
set(CMAKE_CXX_STANDARD 17)
set(SOURCES "./src/logger.cc" "./src/indexUtils.cc" "./src/walkDir.cc" "./src/indexer.cc" "./src/khoj.cc")
set(INCLUDES "./include/logger.hh" "./include/walkDir.hh" "./include/indexer.hh" "./includ/indexUtils.hh")
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Werror")
add_library(sqlite3
 ./third_party/sqlite3/sqlite3.c
 ./third_party/sqlite3/sqlite3.h
)

if (SQLITE_ENABLE_COLUMN_METADATA)
    # Enable the use of SQLite column metadata method
    # Require that the sqlite3 library is also compiled with this flag:
    target_compile_definitions(sqlite3 PUBLIC SQLITE_ENABLE_COLUMN_METADATA)
endif (SQLITE_ENABLE_COLUMN_METADATA)

if (SQLITE_ENABLE_JSON1)
    # Enable JSON1 extension when building sqlite3
    # See more here: https://www.sqlite.org/json1.html
    target_compile_definitions(sqlite3 PUBLIC SQLITE_ENABLE_JSON1)
endif (SQLITE_ENABLE_JSON1)

if(SQLITE_ENABLE_RTREE)
    # Enable RTree extension when building sqlite3
    # See more here: https://sqlite.org/rtree.html
    target_compile_definitions(sqlite3 PUBLIC SQLITE_ENABLE_RTREE)
endif (SQLITE_ENABLE_RTREE)

include(GNUInstallDirs)
install(TARGETS sqlite3
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT libraries)
install(FILES sqlite3.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT headers)

add_executable(khoj ${SOURCES})
target_link_libraries(khoj sqlite3)
include_directories(include)
