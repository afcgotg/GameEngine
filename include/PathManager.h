#include <string>

#ifndef __PathManager__
#define __PathManager__

class PathManager
{
    public:
        static PathManager* Instance();
        ~PathManager(){};

        void SetExecutionPath(char* path);

        std::string GetExecutionPath() const;
        std::string GetAssetsPath() const;

    private:
        PathManager(){};
        static PathManager* mInstance;

        std::string mExecutionPath;

        #if defined(_WIN64)
        const char* mSlash = "\\";
        #elif defined(__unix__) && defined(__x86_64__)
        const char* mSlash = "/";
        #endif
};

typedef PathManager ThePathManager;

#endif