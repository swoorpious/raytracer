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


enum class EPathType : unsigned short int {
    Project,
    Output,
};
// could update with more path types
// malloc'd string is never freed here
// caller may free whenever
static std::shared_ptr<std::string> getPathTo(const std::string& path, EPathType type = EPathType::Project) {
    std::string base;
    switch (type) {
    case EPathType::Project:
        base = PROJECT_DIR; break;
    case EPathType::Output:
        base = OUTPUT_PATH; break;
    default: break;
    }
    return std::make_shared<std::string>(base + std::string(path));
}


#endif
