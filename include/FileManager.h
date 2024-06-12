#include <string>

#ifndef __FileManager__
#define __FileManager__

class FileManager
{
    public:
        static FileManager* Instance();
        ~FileManager(){};

        void SetExecutionPath(char* path);

        std::string GetStatesFilePath() const;
        std::string GetSettingsFilePath() const;

    private:
        FileManager(){};
        static FileManager* mInstance;

        std::string mExecutionPath;

        #if defined(_WIN64)
        const char* mSlash = "\\";
        #elif defined(__unix__) && defined(__x86_64__)
        const char* mSlash = "/";
        #endif
};

typedef FileManager TheFileManager;

#endif