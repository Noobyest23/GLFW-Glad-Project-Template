#ifndef NAPP_SETTINGS
#define NAPP_SETTINGS

#include <unordered_map>
#include <string>

class Settings {
public:
	static void Load(const std::string& filepath);

	static bool GetBool(const std::string& key);
	static int GetInt(const std::string& key);
	static float GetFloat(const std::string& key);
	static std::string GetString(const std::string& key);

private:
	static std::unordered_map<std::string, std::string> settings;
};

#endif
