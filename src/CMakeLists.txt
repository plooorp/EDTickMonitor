find_package(Qt6 REQUIRED COMPONENTS Core Network)
qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
	edsm.cpp
	edsm.hpp
	globals.hpp
	main.cpp
	tickmonitor.cpp
	tickmonitor.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE FALSE)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Core Qt::Network)
