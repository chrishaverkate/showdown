set(target_name ${CMAKE_PROJECT_NAME}_lib)

add_library(${target_name}
	OBJECT
		controller_impl.cpp
		factory.cpp

		models/session.cpp

		views/delta_table.cpp
		views/home.cpp
		views/timeline.cpp
		views/time_table.cpp
)

target_link_libraries(${target_name}
	PUBLIC
		${CMAKE_PROJECT_NAME}_includes
)

set_target_properties(${target_name}
	PROPERTIES
		C_STANDARD 11
		CXX_STANDARD 17
)
