#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>

void walkDir(std::string directory, std::function<void(std::string)>);
