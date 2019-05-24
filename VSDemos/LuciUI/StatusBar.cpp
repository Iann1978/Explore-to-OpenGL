#include "prebuild.h"
#include "StatusBar.h"
#include <Text.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>


StatusBar::StatusBar()
{
	// time
	time = new Text(timestr, 1920/2-150, 5, 24);
	
	UpdateTime();

	carrier = new Text("china mobile", 0, 5, 24);
}


StatusBar::~StatusBar()
{
	delete time;
}


void StatusBar::Update()
{
	UpdateTime();
}

void StatusBar::Render()
{
	RenderTime();
	carrier->Render();
}

void StatusBar::UpdateTime()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(now);

	struct tm buf;
	errno_t err = localtime_s(&buf, &start_time);
	if (std::strftime(timestr, sizeof(timestr), "%F %H:%M:%S", &buf)) {
		int a = 0;
		int b = 0;
	}
}
void StatusBar::RenderTime()
{
	time->Render();
}