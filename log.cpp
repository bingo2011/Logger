#include "log.h"

#include <list>
#include <iostream>

typedef std::list<std::pair <std::string, LogComponent *> > ComponentList;
typedef std::list<std::pair <std::string, LogComponent *> >::iterator ComponentListI;

static 
ComponentList *GetComponentList (void)
{
  static ComponentList components;
  return &components;
}

LogComponent::LogComponent (char const * name)
  : m_levels (0), m_name (name)
{
  //EnvVarCheck (name);

  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      if (i->first == name)
        {
          std::cerr << "Log component \""<<name<<"\" has already been registered once." << std::endl;
        }
    }
  components->push_back (std::make_pair (name, this));
}

bool
LogComponent::IsEnabled (enum LogLevel level) const
{
  //  LogComponentEnableEnvVar ();
  return (level & m_levels) ? 1 : 0;
}

bool
LogComponent::IsNoneEnabled (void) const
{
  return m_levels == 0;
}

void
LogComponent::Enable (enum LogLevel level)
{
  m_levels |= level;
}

void
LogComponent::Disable (enum LogLevel level)
{
  m_levels &= ~level;
}

char const *
LogComponent::Name (void) const
{
  return m_name;
}

void
LogComponentEnable (char const *name, enum LogLevel level)
{
  ComponentList *components = GetComponentList ();
  ComponentListI i;
  for (i = components->begin ();
       i != components->end ();
       i++)
    {
      if (i->first.compare (name) == 0)
        {
          i->second->Enable (level);
          return;
        }
    }
    if (i == components->end())
      {
	// nothing matched
        LogComponentPrintList();
        NS_FATAL_ERROR ("Logging component \"" << name <<
                        "\" not found. See above for a list of available log components");
    }
}

void
LogComponentEnableAll (enum LogLevel level)
{
  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      i->second->Enable (level);
    }
}

void
LogComponentDisable (char const *name, enum LogLevel level)
{
  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      if (i->first.compare (name) == 0)
        {
          i->second->Disable (level);
          break;
        }
    }
}

void
LogComponentDisableAll (enum LogLevel level)
{
  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      i->second->Disable (level);
    }
}
