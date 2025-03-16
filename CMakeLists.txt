cmake_minimum_required(VERSION 3.14)
project(game)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск системных зависимостей
find_package(OpenGL REQUIRED)

if(UNIX)
    # Используем pkg-config для SDL2
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

    include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
    )
elseif(WIN32)
    # Конфигурация SDL2
    set(SDL2_DIR ${CMAKE_SOURCE_DIR}/vendor/SDL2)
    include_directories(
        ${SDL2_DIR}/include/SDL2
    )

    # Конфигурация SDL2_image
    set(SDL2_IMAGE_DIR ${CMAKE_SOURCE_DIR}/vendor/SDL2_image)
    include_directories(
        ${SDL2_IMAGE_DIR}/include/SDL2_image
    )

endif()

# Конфигурация Glad
include_directories(${CMAKE_SOURCE_DIR}/vendor/glad/include)
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c)

# Конфигурация GLM
include_directories(${CMAKE_SOURCE_DIR}/vendor/glm/include)

# Сборка исполняемого файла
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Линковка библиотек
if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        OpenGL::GL
        glad
        ${SDL2_DIR}/lib/SDL2.lib
        ${SDL2_DIR}/lib/SDL2main.lib
        ${SDL2_IMAGE_DIR}/lib/SDL2_image.lib
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        OpenGL::GL
        glad
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        pthread
        dl
    )
endif()

# Копирование DLL для Windows
if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SDL2_DIR}/lib/SDL2.dll
        ${SDL2_IMAGE_DIR}/lib/SDL2_image.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# Настройка подсистемы
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS"
        LINK_FLAGS_RELWITHDEBINFO "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS"
        LINK_FLAGS_MINSIZEREL "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS"
    )
endif()
