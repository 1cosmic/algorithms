install(
    TARGETS algorithms_exe
    RUNTIME COMPONENT algorithms_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
