#ifndef _XML_RESOURCE_HPP_
#define _XML_RESOURCE_HPP_

#include "rapidxml.hpp"
#include "resources/Path.hpp"
#include "resources/Resource.hpp"
#include "resources/ResourceDefs.hpp"

//improve compile time by only instantiating the tempaltes in XmlResource.cpp
extern template class rapidxml::xml_attribute<>;
extern template class rapidxml::xml_node<>;
extern template class rapidxml::xml_document<>;
typedef rapidxml::xml_attribute<> XmlAttribute;
typedef rapidxml::xml_node<> XmlNode;
typedef rapidxml::xml_document<> XmlDoc;

//Macros that make it "easy" to make new XmlResources
#define BEGIN_XML_RESOURCE(className) _DEF_XML_RESOURCE(className,public XmlResource)
#define BEGIN_XML_RESOURCE_INHERITS(className,...) _DEF_XML_RESOURCE(className,public XmlResource,__VA_ARGS__)
#define _DEF_XML_RESOURCE(className,...) class className : __VA_ARGS__ {

#define END_XML_RESOURCE(className) \
}; \
template <> class className* XmlResource::load<className>(const Path& path,XmlNode* node);
//extern template class className* XmlResource::load<className>(const Path& path,XmlNode* node);

#define DEF_XML_RESOURCE_LOAD(className) \
template <> class className* XmlResource::load<className>(const Path& path,XmlNode* node)

class XmlResource : public Resource{
  public:
    XmlResource();
    virtual ~XmlResource();

    /*
    template<class T>
    static T* load(const Path& path, XmlNode* node){
      //This version of the load function should never actually get used
      T* dummy = (XmlResource*)0;
      return new XmlResource();
    }*/
    template<class T>
    static T* load(const Path& path, XmlNode* node);

    template<class T>
    static T* load(const Path& path, char* xml_text){
      rapidxml::xml_document<> doc;
      try{
        doc.parse<
          rapidxml::parse_trim_whitespace
          | rapidxml::parse_normalize_whitespace
        >(xml_text);
      }catch(exception& e){
        raise(MalformedResourceException,path,"Malformed xml");
      }
      XmlNode* node = doc.first_node();
      return load<T>(path,node);
    }
};

#endif

