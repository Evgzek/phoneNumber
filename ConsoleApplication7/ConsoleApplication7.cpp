#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Record {
    string phone;
    string name;
    string address;
};

bool compareRecords(const Record& a, const Record& b) {
    return a.phone < b.phone;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Не удается открыть входной файл" << endl;
        return 1;
    }

    vector<Record> records;
    string line;
    while (getline(inputFile, line)) {
        Record record;
        size_t pos = line.find(',');
        if (pos == string::npos) {
            cout << "Недопустимый формат ввода" << endl;
            return 1;
        }
        record.phone = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(',');
        if (pos == string::npos) {
            cout << "Недопустимый формат ввода" << endl;
            return 1;
        }
        record.name = line.substr(0, pos);
        line.erase(0, pos + 1);
        record.address = line;
        records.push_back(record);
    }

    inputFile.close();

    sort(records.begin(), records.end(), compareRecords);

    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cout << "Не удается открыть выходной файл" << endl;
        return 1;
    }

    for (const auto& record : records) {
        outputFile << record.phone << "," << record.name << "," << record.address << endl;
    }

    outputFile.close();

    return 0;
}

