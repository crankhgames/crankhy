#include "scene/scene-parser.h"
#include <fstream>
#include <algorithm>

#include "debug.h"

namespace Crankhy{
    
    struct SceneParserEntityInitializer{
        std::string s;
    };

    void parseSceneFile(const char* filename){
        std::fstream stream(filename);
        
        if (!stream.is_open()){
            debug::error("File not opened !");
        }

        debug::log("File ", filename, "'s content: ");
        std::string line;
        while (std::getline(stream, line)){
            debug::log(line);
        }
        debug::log("");
    }
}