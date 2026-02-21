#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}
void Screen1Presenter::rpm(int data)
{
	view.rpm(data);
}
void Screen1Presenter::speed(int data)
{
	view.speed(data);
}
void Screen1Presenter::soc(int data)
{
	view.soc(data);
}
void Screen1Presenter::battery1(battery_t data)
{
	view.battery1(data);
}
void Screen1Presenter::motor(motor_t data)
{
	view.motor(data);
}
void Screen1Presenter::target(target_t data)
{
	view.target(data);
}
void Screen1Presenter::time(char *data)
{
	view.time(data);
}
void Screen1Presenter::gpsspeed(int data)
{
	view.gpsspeed(data);
}
