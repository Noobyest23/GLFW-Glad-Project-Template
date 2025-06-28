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
		std::string key, eq;
		if (iss >> key >> eq && eq == "=") {
			std::string value;
			std::getline(iss >> std::ws, value);
			settings[key] = value;
		}
	}
	file.close();
}

void Settings::Save(const std::string& filepath) {
	std::ofstream file(filepath);
	if (!file.is_open()) {
		std::cerr << "Failed to open settings file for writing: " << filepath << "\n";
		return;
	}

	for (const auto& [key, value] : settings) {
		file << key << " = " << value << "\n";
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

void Settings::Set(const std::string& key, const std::string& value) {
	settings[key] = value;
}

void Settings::Set(const std::string& key, bool value) {
	settings[key] = value ? "true" : "false";
}

void Settings::Set(const std::string& key, int value) {
	settings[key] = std::to_string(value);
}

void Settings::Set(const std::string& key, float value) {
	settings[key] = std::to_string(value);
}

