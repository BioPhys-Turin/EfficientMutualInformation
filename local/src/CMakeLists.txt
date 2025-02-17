add_executable(hk
    main.cpp)


if(OpenMP_CXX_FOUND)
    target_link_libraries(hk PUBLIC OpenMP::OpenMP_CXX)
endif()