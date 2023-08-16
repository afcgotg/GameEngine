#include "XMLFile.h"
#include <iostream>

XMLFile::XMLFile()
{
    mIterationMode = false;
}

bool XMLFile::LoadDocument(std::string filePath)
{
    if(mXMLDocument.LoadFile(filePath.c_str())){
        std::cout << mXMLDocument.ErrorStr() << std::endl;
        return false;
    }
    mElementsStack.push_back(mXMLDocument.RootElement());
    return true;
}

bool XMLFile::GoToElement(std::string elementName)
{
    for(tinyxml2::XMLElement* e = mElementsStack.back()->FirstChildElement(); e != 0; e = e->NextSiblingElement())
    {
        if(e->Value() == elementName){
            mElementsStack.push_back(e);
            return true;
        }
    }    
    return false;
}

bool XMLFile::IterateOverElement(std::string elementName)
{
    if(!mIterationMode)
    {
        for(tinyxml2::XMLElement* e = mElementsStack.back()->FirstChildElement(); e != 0; e = e->NextSiblingElement())
        {
            if(e->Value() == elementName){
                mElementsStack.push_back(e);
                mIterationMode = true;
                return true;
            }
        }   
    }
    else
    {
        for(tinyxml2::XMLElement* e = mElementsStack.back()->NextSiblingElement(); e != 0; e = e->NextSiblingElement())
        {
            if(e->Value() == elementName){
                mElementsStack.back() = e;
                return true;
            }
        }

        mIterationMode = false;
        return false;
    }
 
    return false;
}

void XMLFile::GoBack()
{
    if(!mElementsStack.empty())
        mElementsStack.pop_back();
}

bool XMLFile::GetIntAttribute(std::string attributeName, int* num)
{
    if(!mElementsStack.empty())
    {
        mElementsStack.back()->QueryIntAttribute(attributeName.c_str(), num);
        return true;
    }
    return false;
}

bool XMLFile::GetStringAttribute(std::string attributeName, std::string* string)
{
    if(!mElementsStack.empty())
    {
        *string = std::string(mElementsStack.back()->Attribute(attributeName.c_str()));
        return true;
    }
    return false;
}

bool XMLFile::GetBoolAttribute(std::string attributeName, bool* boolean)
{
    if(!mElementsStack.empty())
    {
        mElementsStack.back()->QueryBoolAttribute(attributeName.c_str(), boolean);
        return true;
    }
    return false;
}