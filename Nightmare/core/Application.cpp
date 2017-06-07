
#include "application.h"

namespace dream
{

Application::Application(std::shared_ptr<ApplicationManager> manager, const char* id) :
	application_manager(manager), 
	app_id(id)
{
	this->exit = false;
}

Application::~Application(void)
{
	this->Release();
}

bool Application::IsExit(void) const
{
	return this->exit;
}

PApplicationManager Application::GetApplicationManager(void)
{
	return this->application_manager.get();
}

} // namespace dream
