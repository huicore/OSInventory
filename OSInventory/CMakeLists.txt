cmake_minimum_required(VERSION 3.15)
project(OSInventory)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Явное указание пути к SFML
set(SFML_ROOT "C:/SFML")  # Или ваш реальный путь установки
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")

# Поиск SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Настройка путей включения
include_directories(
    include
    ${SFML_INCLUDE_DIR}
    "${SFML_ROOT}/include"  # Явное добавление пути к заголовкам
)

# Источники
file(GLOB SOURCES "src/*.cpp")

# Создание исполняемого файла
add_executable(OSInventory ${SOURCES})

# Линковка SFML
target_link_libraries(OSInventory
    sfml-graphics
    sfml-window
    sfml-system
)
add_custom_command(TARGET OSInventory POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:OSInventory>/resources
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/Roboto-Regular.ttf
        $<TARGET_FILE_DIR:OSInventory>/resources/
    COMMENT "Copying font file to output directory"
)

# Копирование DLL (только для Windows)
if(WIN32)
    add_custom_command(TARGET OSInventory POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_ROOT}/bin/sfml-graphics-2.dll"
        "${SFML_ROOT}/bin/sfml-window-2.dll"
        "${SFML_ROOT}/bin/sfml-system-2.dll"
        $<TARGET_FILE_DIR:OSInventory>
    )
endif()