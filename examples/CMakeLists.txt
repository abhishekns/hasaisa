if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()


add_executable (main)

target_sources (main
PUBLIC
  main.cpp example.cpp
)

target_compile_features(main PUBLIC cxx_std_17)
target_include_directories (main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../src)
target_link_libraries (main LINK_PUBLIC flexiobjects)