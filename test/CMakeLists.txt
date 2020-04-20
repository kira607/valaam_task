project(signature_test)


add_executable(${PROJECT_NAME}
        test_smth.cpp
        )

target_link_libraries(${PROJECT_NAME}
        ${GMOCK_LIBRARIES}
        ${GMOCK_MAIN_LIBRARIES}
        )


add_test(
        NAME
        test_signature
        COMMAND
        ${PROJECT_NAME}
)
