cmake_minimum_required(VERSION 3.5)


project(FxCommonUI)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


file(GLOB HEADER_FILES *.h)
file(GLOB SOURCE_FILES *.cpp)
file(GLOB UI_FILES *.ui)
file(GLOB RESOURCE_FILES *.qrc)

source_group("Header Files" FILES ${HEADER_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Forms" FILES ${UI_FILES} ${RESOURCE_FILES})

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${UI_FILES} ${RESOURCE_FILES} )

find_package(Qt${QT_VERSION_NUMBER} COMPONENTS Widgets)

target_link_libraries(${PROJECT_NAME}
Qt${QT_VERSION_NUMBER}::Core
Qt${QT_VERSION_NUMBER}::Widgets
)

set_target_properties( ${PROJECT_NAME} PROPERTIES
    FOLDER "CommonUI"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PRODUCT_NAME}
)