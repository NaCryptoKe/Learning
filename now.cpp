static void Log(const std::string& text) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::put_time(std::localtime(&now), "%T") << ": " << text << '\n';
}

int main() {
    Log ("Hello, world!");
    Log ("Hello, world!");
    Log ("Hello, world!");
}
