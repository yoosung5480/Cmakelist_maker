#include <iostream>
#include <cstdlib> // system() 함수 사용을 위해 포함

void createDirectory(const std::string& name) {
    // 명령어 문자열을 생성
    std::string command = "mkdir " + name;

    // system() 함수를 사용하여 명령어 실행
    int result = system(command.c_str());

    // 명령어 실행 결과 확인
    if (result == 0) {
        std::cout << "Directory '" << name << "' created successfully." << std::endl;
    } else {
        std::cerr << "Error creating directory '" << name << "'." << std::endl;
    }
}

int main() {
    std::string name;

    std::cout << "Enter directory name: ";
    std::cin >> name;

    createDirectory(name);

    return 0;
}
