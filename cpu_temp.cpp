#include <print>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>

void copy_temp(const std::string& home) {
    for(const auto& entry : std::filesystem::directory_iterator("/sys/class/hwmon")) {
        for(const auto& file : std::filesystem::directory_iterator(entry)) {
            auto label_path = file.path();
            if(label_path.filename().string().find("temp") == 0 && label_path.string().find("_label") != std::string::npos) {
                std::ifstream label_file(label_path.string());
                std::string label;
                if(label_file && std::getline(label_file, label)) {
                    if(label == "Tctl") {
                        std::string input_path = label_path.string();
                        input_path.replace(input_path.find("_label"), 6, "_input");
                        
                        std::ifstream input_file(input_path);
                        std::ofstream destination(home + "/.cpu_temp");

                        destination << input_file.rdbuf();
                        return;
                    }
                }
            }
        }
    }

}

int main() {
    const char* home = getenv("HOME");
    if(home == nullptr) {
        std::println("HOME variable is not set."); 
        return 1;
    }

    while(true) {
        copy_temp(home);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
