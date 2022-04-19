########################## QT ######################################
find_package(Qt5 COMPONENTS Widgets OpenGL)

######################### spdlog ###################################
find_package(spdlog CONFIG REQUIRED)

find_package(qtadvanceddocking CONFIG REQUIRED)

add_subdirectory(Vendors)
add_subdirectory(Runtime)
add_subdirectory(App)

