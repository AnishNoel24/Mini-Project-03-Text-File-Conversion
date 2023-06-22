#include <iostream>
#include <fstream>
#include <ctime>
#include <cctype>

// Function to convert file to upper case
void convert_to_upper_case(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    std::ofstream outfile(file_path + ".tmp");
    if (!outfile) {
        std::cerr << "Failed to create temporary file" << std::endl;
        file.close();
        return;
    }

    char c;
    while (file.get(c)) {
        outfile.put(std::toupper(c));
    }

    file.close();
    outfile.close();

    std::remove(file_path.c_str());
    std::rename((file_path + ".tmp").c_str(), file_path.c_str());
}

int main() {
    // File sizes to test
    int file_sizes[] = {200, 400, 600, 800, 1000};  // MB

    // Perform conversion for each file size
    int num_sizes = sizeof(file_sizes) / sizeof(file_sizes[0]);
    for (int i = 0; i < num_sizes; i++) {
        int size = file_sizes[i];
        std::string file_path = "input_" + std::to_string(size) + "mb.txt";

        // Create text file of given size (filled with random characters)
        std::ofstream file(file_path);
        if (!file) {
            std::cerr << "Failed to create file: " << file_path << std::endl;
            continue;
        }
        for (int j = 0; j < size * 1024 * 1024; j++) {
            file.put('a');
        }
        file.close();

        // Measure execution time
        clock_t start_time = clock();
        convert_to_upper_case(file_path);
        clock_t end_time = clock();

        // Calculate and print execution time
        double execution_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        std::cout << "File size: " << size << "MB, Execution time: " << execution_time << " seconds" << std::endl;
    }

    return 0;
}
