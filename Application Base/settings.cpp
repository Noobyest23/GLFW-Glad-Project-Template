#include "Settings.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::unordered_map<std::string, std::string> Settings::settings;

void Settings::Load(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cerr << "Failed to open settings file: " << filepath << "\n";
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		auto comment = line.find("//");
		if (comment != std::string::npos) line = line.substr(0, comment);

		std::istringstream iss(line);
		std::string key, eq, value;
		if (iss >> key >> eq >> value && eq == "=") {
			settings[key] = value;
		}
	}
	file.close();
}

bool Settings::GetBool(const std::string& key) {
	auto val = settings[key];
	return val == "true" || val == "1";
}

int Settings::GetInt(const std::string& key) {
	return std::stoi(settings[key]);
}

float Settings::GetFloat(const std::string& key) {
	return std::stof(settings[key]);
}

std::string Settings::GetString(const std::string& key) {
	return settings[key];
}
