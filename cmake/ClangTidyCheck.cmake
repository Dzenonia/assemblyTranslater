option(CLANG_TIDY_CHECK "Run clang-tidy before the build")

if(CLANG_TIDY_CHECK)
  find_program(CLANG_TIDY_EXE NAMES "clang-tidy" "clang-tidy-12" REQUIRED)

  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()
