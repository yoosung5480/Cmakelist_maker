#include <iostream>
#include <vector>
#include <string>

class Maker{
        int type;
    public:
        enum {CPP_EXE, CPP_LIB, C_EXE, C_LIB};
        Maker(int t): type(t){}
        virtual int get_target(const std::string& _target)=0;
        virtual int get_source(const std::string& _source)=0;
        virtual int remove_target(const std::string& _target)=0;
        virtual int remove_source(const std::string& _source)=0;
        virtual int show_target(const std::string& _target)=0;
        virtual int show_source(const std::string& _source)=0;
        virtual int build()=0;
};




class CppExe : public Maker{
    private:
        std::string target;
        std::vector <std::string> sources;
        // std::vector <std::string> Cmakelists;
    public:
        CppExe(): Maker(CPP_EXE){}
        int get_target(const std::string& _target){
            if(_target.empty()){return 1;}
            target = _target;
            return 0;
        }
        int get_source(const std::string& _source){
            if(_source.empty()){return 1;}
            sources.push_back(_source);
            return 0;
        } 

        int remove_target(const std::string& _target){

        }
        int remove_source(const std::string& _source){ //단순 선형 탐색-> linked list로 구현
            
        }

        int show_target(const std::string& _target){

        }
        int show_source(const std::string& _source){
            
        }

        int build(){}


};

void make_clists(std::string &clist_str, std::string &locate){

}

void make_dir(std::string &name, std::string &locate){

}

int CppExe::build(){
    std::string target_clist;
    std::string lib_clist;
    std::string locate = ".";//현재 디렉토리

    //target_clist
    target_clist += "# main\n";
    target_clist += "   cmake_minimum_required(VERSION 3.10)\n";
    target_clist += "   set(CMAKE_CXX_STANDARD 17)\n";
    target_clist += "   set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n";
    target_clist += "   add_subdirectory( lib )\n";
    target_clist += "   add_executable( "+ target +" "+ target +".cpp )\n";
    target_clist += "   target_link_libraries("+ target +" "+ target +")\n";
    target_clist += "   target_include_directories( "+ target +" PUBLIC \"${PROJECT_SOURCE_DIR}/include\" )\n";
    target_clist += "   set_target_properties( "+ target +" PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )\n";

    //include, lib 디렉토리 만들기
    std::string include = "include";
    std::string lib = "lib";
    make_dir(include, locate);
    make_dir(lib, locate);
    locate += "/"+lib;
    
    //lib_clist
    lib_clist = "add_subdirectory("+ target +")";
    make_clists(lib_clist, locate);
    for(auto source: sources){
        make_dir(source, locate);
    }

    for(auto source: sources){
        std::string temp;
        locate += "/"+source;
        /*
            add_library(MultiThreadTracer MultiThreadTracer.cpp)
            target_compile_options(MultiThreadTracer PUBLIC -g -Wall)
            target_include_directories(MultiThreadTracer PUBLIC "${PROJECT_SOURCE_DIR}/include")
            target_link_libraries(MultiThreadTracer ProcessorTracer Decoder)
        */
        temp += "add_library("+source+" "+source+".cpp)\n";
        temp += "target_compile_options("+source+" PUBLIC -g -Wall)\n";
        temp += "target_include_directories("+source+" PUBLIC \"${PROJECT_SOURCE_DIR}/include\")\n";
        temp += "target_link_libraries("+source+" "+target+" Decoder)\n";
        make_clists(temp, locate);
    }
}