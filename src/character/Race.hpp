#ifndef _RACE_HPP_
#define _RACE_HPP_

#include "resources/XmlResource.hpp"

class Stats;
class Modifier;
class Race : public XmlResource{
  public:
    Race(const string& name, const string& description, Modifier* modifier);
    ~Race();
    Modifier* getModifier() const;
    const string& getName() const;
    const string& getDescription() const;
  private:
    string _name;
    string _description;
    Modifier* _modifier;
};
MAKE_XML_RESOURCE(Race)

#endif

