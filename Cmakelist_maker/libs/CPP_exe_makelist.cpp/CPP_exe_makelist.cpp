#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <fstream>

class Maker{
        int type;
    public:
        enum {CPP_EXE, CPP_LIB, C_EXE, C_LIB};
        Maker(int t): type(t){}
        virtual int get_target(const std::string& _target){return 0;}
        virtual int get_source(const std::string& _source){return 0;}
        virtual int remove_target(const std::string& _target){return 0;}
        virtual int remove_source(const std::string& _source){return 0;}
        virtual int show_target(const std::string& _target){return 0;}
        virtual int show_source(const std::string& _source){return 0;}
        virtual int build(std::string& locate){return 0;}
};




class CppExe : public Maker{
    private:
        std::string target;
        std::list <std::string> sources;
        // std::vector <std::string> Cmakelists;
    public:
        CppExe(): Maker(CPP_EXE){}
        int get_target(const std::string& _target){
            if(_target.empty()){
                std::cerr << "no input for target name" << std::endl;
                return 1;
            }
            target = _target;
            return 0;
        }
        int get_source(const std::string& _source){
            if(_source.empty()){
                std::cerr << "no input for source name" << std::endl;
                return 1;
            }
            sources.push_back(_source);
            return 0;
        } 


        //앞의 것부터 차례대로 요소를 없앤다.
        int remove_target(const std::string& _target){
            if(_target.empty()){
                std::cerr << "no input for target name to remove" << std::endl;
                return 1;
            }
            target= "";
            return 0;
        }
        int remove_source(const std::string& _source){ //단순 선형 탐색-> linked list로 구현
            auto iterator = std::find(sources.begin(), sources.end(), _source);
            if(iterator == sources.end()){
                std::cerr << "data not found" << std::endl;
                return 1;
            }
            sources.erase(iterator);
            return 0;
        }

        int show_target(){
            if(target.empty()){
                std::cerr << "target not exitst" << std::endl;
                return 1;
            }
            std::cout << "target name : " + target << std::endl;
            return 0;
        }
        int show_source(){
            for(auto source : sources){
                if(target.empty()){
                    std::cerr << "source not exitst" << std::endl;
                    return 1;
                }
                std::cout << "source name : " + target << std::endl;
            }
            return 0;
        }

        int build(std::string& locate);


};

// 성공적으로 CMakeLIsts생성시 0반환
int make_clists(std::string &clist_str, std::string &path){
    if(clist_str.empty() || path.empty()){
        std::cerr << "no input for CMakeLIsts or path" << std::endl;
        return 1;
    }
    std::string temp_path = path + "/CMakeLists.txt";
    std::ofstream file(temp_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return 1;
    }
    file << clist_str;
    file.close();
    
    
    return 0;

}


// 성공적으로 디렉토리 생성시, 0반환
int make_dir(std::string &path){
    if(path.empty()){
        std::cerr << "no input for directory name" << std::endl;
        return 1;
    }
    std::string command = "mkdir -p " + path;
    return system(command.c_str());
}

int CppExe::build(std::string& path){
    std::string lib_path = path + "/libs";
    make_dir(lib_path);
    std::string include_path = path + "/include";
    make_dir(include_path);

    //target_clist
    std::string target_clist;
    target_clist += "# main\n";
    target_clist += "   cmake_minimum_required(VERSION 3.10)\n";
    target_clist += "   set(CMAKE_CXX_STANDARD 17)\n";
    target_clist += "   set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n";
    target_clist += "   add_subdirectory( lib )\n";
    target_clist += "   add_executable( "+ target +" "+ target +".cpp )\n";
    target_clist += "   target_link_libraries("+ target +" "+ target +")\n";
    target_clist += "   target_include_directories( "+ target +" PUBLIC \"${PROJECT_SOURCE_DIR}/include\" )\n";
    target_clist += "   set_target_properties( "+ target +" PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )\n";
    make_clists(target_clist, path);
    std::cout << target_clist << std::endl;

    std::string lib_clist;
    lib_clist = "add_subdirectory("+ target +")\n";
    make_clists(lib_clist, lib_path);
    std::cout << lib_clist << std::endl;

    for(auto source : sources){
        std::string source_path = lib_path + "/" + source;
        make_dir(source_path);

        std::string temp;
        temp += "add_library("+source+" "+source+".cpp)\n";
        temp += "target_compile_options("+source+" PUBLIC -g -Wall)\n";
        temp += "target_include_directories("+source+" PUBLIC \"${PROJECT_SOURCE_DIR}/include\")\n";
        temp += "target_link_libraries("+source+" "+target+" Decoder)\n";
        make_clists(temp, source_path);
        std::cout << temp << std::endl;
    }
    return 0;
}


int main(){

    CppExe temp;
    temp.get_target("main");
    temp.get_source("source1");
    temp.get_source("source2");
    temp.show_target();
    temp.show_source();
    
    temp.remove_source("source1");
    temp.remove_source("source3");
    temp.remove_target("main");
    temp.show_target();
    temp.show_source();

    temp.get_target("new_main");
    temp.get_source("new_source1");
    std::string location = "example";
    temp.build(location);

    return 0;   
}