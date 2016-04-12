#ifndef TAPEWORMS_MAIN_H
#define TAPEWORMS_MAIN_H

// Suppressing certain IDE warnings
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedImportStatement"

#include <cstdio>

#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define _USE_MATH_DEFINES // Windows OS requires that
#pragma clang diagnostic pop

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <time.h>

#define WIDTH 600
#define HEIGHT 600
#define ROT 5
#define NUMBER_OF_PLAYERS 1

static const std::string app_name = "Tapeworms";
static const std::string app_resources = "Resources/";
static const std::string app_font = "arial.ttf";
//static const std::string player_texture = "red_arrow.png";

#endif //TAPEWORMS_MAIN_H
