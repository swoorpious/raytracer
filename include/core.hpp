// copyright 2026 swaroop.
#pragma once

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

#include "vec3.hpp"
#include "interval.hpp"
#include "util.hpp"


// could update with more path types
// malloc'd string is never freed here
// caller may free whenever
static std::shared_ptr<std::string> getPathTo(const char* path) {
    return std::make_shared<std::string>(OUTPUT_PATH + std::string(path));
}


#endif
