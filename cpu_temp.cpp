#include <print>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>

std::filesystem::path find_tctl_temp() {
    for(const auto& entry : std::filesystem::directory_iterator("/sys/class/hwmon")) {
        for(const auto& file : std::filesystem::directory_iterator(entry)) {
            std::filesystem::path label_path = file.path();
            if(label_path.filename().string().find("temp") == 0 && label_path.string().find("_label") != std::string::npos) {
                std::ifstream label_file(label_path);
                std::string label;
                if(label_file && std::getline(label_file, label)) {
                    if(label == "Tctl") {
                        std::string input_path = label_path.string();
                        input_path.replace(input_path.find("_label"), 6, "_input");
                        return input_path;
                    }
                }
            }
        }
    }
    return "";
}

template<typename... Args>
void log(std::string_view fmt, Args&&... args) {
    static std::ofstream logfile("cpu_temp.log", std::ios::app);
    
    auto now_seconds = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    auto local_time = std::chrono::zoned_time {std::chrono::current_zone(), now_seconds};
    std::println(logfile, "[{:%Y-%m-%d %H:%M:%S}] {}", local_time, std::vformat(fmt, std::make_format_args(args...)));
    logfile.flush();
}

void copy_temp(const std::filesystem::path& home, const std::filesystem::path& tctl_input_path) {
    std::filesystem::path dest = home/".cpu_temp";
    std::ofstream(dest) << std::ifstream(tctl_input_path).rdbuf();
    log("Copied tctl temp ({}) to {}.", tctl_input_path.string(), dest.string());
}

int main() {
    const char* home = getenv("HOME");
    if(home == nullptr) {
        log("HOME variable is not set."); 
        return 1;
    }

    std::filesystem::path tctl_input_path = find_tctl_temp();
    if(tctl_input_path == "") {
        log("Could not find tctl temp path.");
        return 1;
    }

    while(true) {
        copy_temp(home, tctl_input_path);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
