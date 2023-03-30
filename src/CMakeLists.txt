if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()

add_library (flexiobjects SHARED)
target_sources(flexiobjects PUBLIC flexibleObjects.hpp)
set_target_properties(flexiobjects PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (flexiobjects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(flexiobjects PUBLIC cxx_std_17)
