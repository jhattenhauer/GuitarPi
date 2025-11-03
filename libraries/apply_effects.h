#include <iostream>
#include <vector>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;

void apply_effects(){
    std::ifstream file("pedals.json");
    json data = json::parse(file);

    for (auto& pedal : data["pedal_settings"]) {
        std::string id = pedal["id"];
        bool enabled = pedal.value("enabled", 0);

        std::cout << "Pedal: " << id << " (enabled: " << enabled << ")\n";

        if (pedal.contains("gain"))
            std::cout << "  gain: " << pedal["gain"] << "\n";
        if (pedal.contains("drive"))
            std::cout << "  drive: " << pedal["drive"] << "\n";
        if (pedal.contains("tone"))
            std::cout << "  tone: " << pedal["tone"] << "\n";
        if (pedal.contains("time"))
            std::cout << "  time: " << pedal["time"] << "\n";
        if (pedal.contains("feedback"))
            std::cout << "  feedback: " << pedal["feedback"] << "\n";
        if (pedal.contains("mix"))
            std::cout << "  mix: " << pedal["mix"] << "\n";
        if (pedal.contains("frequency"))
            std::cout << "  frequency: " << pedal["frequency"] << "\n";
        if (pedal.contains("depth"))
            std::cout << "  depth: " << pedal["depth"] << "\n";
        if (pedal.contains("mode"))
            std::cout << "  mode: " << pedal["mode"] << "\n";
    }
}