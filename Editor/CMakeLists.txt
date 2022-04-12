########################## QT #################################
find_package(Qt5 COMPONENTS Widgets OpenGL)
if(Qt5_FOUND)
    message("FOUND QT")
else()
    message("NOT FOUND QT")
endif()

add_subdirectory(Vendors)
add_subdirectory(Runtime)
add_subdirectory(App)

