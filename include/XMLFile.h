#include "../tinyxml2/include/tinyxml2.h"
#include <list>
#include <string>

#ifndef __XMLFile__
#define __XMLFile__

class XMLFile
{
    public:
        XMLFile();

        bool LoadDocument(std::string filePath);
        bool GoToElement(std::string elementName);
        bool IterateOverElement(std::string elementName);
        void GoBack();
        bool GetIntAttribute(std::string attributeName, int* num);
        bool GetStringAttribute(std::string attributeName, std::string* string);
        bool GetBoolAttribute(std::string attributeName, bool* boolean);

    private:
        tinyxml2::XMLDocument mXMLDocument;
        tinyxml2::XMLElement* mpParentRoot;
        std::list<tinyxml2::XMLElement*> mElementsStack;

        bool mIterationMode;
};

#endif