#include "../tinyxml2/include/tinyxml2.h"
#include <list>
#include <string>

#ifndef __XMLFile__
#define __XMLFile__

class XMLFile
{
    public:
        XMLFile(std::string filePath);

        bool LoadDocument();
        bool GoToElement(std::string elementName);
        void GoBack();
        bool GetIntAttribute(std::string attributeName, int* num);
        bool GetStringAttribute(std::string attributeName, std::string* string);
        bool GetBoolAttribute(std::string attributeName, bool* boolean);

    private:
        std::string mFilePath;

        tinyxml2::XMLDocument mXMLDocument;
        tinyxml2::XMLElement* mpParentRoot;
        std::list<tinyxml2::XMLElement*> mElementsStack;
};

#endif