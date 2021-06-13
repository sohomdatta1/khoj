#pragma once
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

void walkDir(std::string directory, std::function<void(std::string)>);
