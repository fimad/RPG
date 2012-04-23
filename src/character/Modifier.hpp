#ifndef _MODIFIER_HPP_
#define _MODIFIER_HPP_

#include "resources/XmlResource.hpp"
#include "character/Stats.hpp"

//The reason this is a resource is to move modifier specific loading from Race and Class to here
//I can't think of a case where a file will contain just a modifier
class Modifier : public XmlResource{
  public:
    Modifier(const string& description);
    virtual ~Modifier();
    virtual int valueFor(Stats::Stat stat);
    void setValueFor(Stats::Stat stat, int value);
    const string& getDescription() const;
  private:
    string _description;
    map<Stats::Stat,int> _values;
};
MAKE_XML_RESOURCE(Modifier)

#endif

