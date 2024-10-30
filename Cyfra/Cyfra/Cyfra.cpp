#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

void loadData(const std::string& filename, std::unordered_map<int, int>& data) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id, value;
        char equalSign;
        if (iss >> id >> equalSign >> value && equalSign == '=') {
            data[id] = value;
        }
    }
}

void saveData(const std::string& filename, const std::unordered_map<int, int>& data) {
    std::ofstream file(filename);

    for (const auto& pair : data) {
        file << pair.first << " = " << pair.second << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string filename = "data.txt"; // имя файла со стартовыми данными
    std::unordered_map<int, int> data;

    // Загрузка данных из файла
    loadData(filename, data);

    int id, newValue;
    char choice;

    while (true) {
        std::cout << "Введите ID для обновления (или введите -1 для выхода): ";
        std::cin >> id;

        if (id == -1) {
            break; // выход из приложения
        }

        std::cout << "Введите новое значение для ID " << id << ": ";
        std::cin >> newValue;

        // Обновление значения данных
        if (data.find(id) != data.end()) {
            data[id] = newValue;
            std::cout << "Сообщение для отправки: Обновлено значение для ID " << id << " на " << newValue << std::endl;
        }
        else {
            std::cout << "ID не найден. Добавление нового ID." << std::endl;
            data[id] = newValue;
            std::cout << "Сообщение для отправки: Добавлено новое значение для ID " << id << " = " << newValue << std::endl;
        }

        // Сохранение обновленных данных в файл
        saveData(filename, data);
    }

    return 0;
}