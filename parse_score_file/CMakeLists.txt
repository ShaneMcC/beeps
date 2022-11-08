cmake_minimum_required(VERSION 3.0)

project(
    score2beep
    VERSION 0.9
    LANGUAGES C
)

add_executable(score2beep parse_score_file.c main.c)
target_link_libraries(score2beep m)

