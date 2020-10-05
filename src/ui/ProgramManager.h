#ifndef _PROGRAMMANAGER_H_
#define _PROGRAMMANAGER_H_

#include <ResourceManager.h>
#include <Singleton.h>
class Program;

class ProgramManager : public ResourceManager,
		       public Singleton<ProgramManager> {
    public:
	ProgramManager();

	Program *create(const std::string &name);

    protected:
	Resource *create(const std::string &name,
			 Resource::Handler handler) override;
};

#endif //_PROGRAMMANAGER_H_
