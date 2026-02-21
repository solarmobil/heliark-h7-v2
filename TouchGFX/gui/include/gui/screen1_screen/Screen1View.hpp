#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void rpm(int data);
    virtual void speed(int data);
    virtual void soc(int data);
    virtual void battery1(battery_t data);
    virtual void motor(motor_t data);
    virtual void target(target_t data);
    virtual void time(char *data);
    virtual void gpsspeed(int data);
protected:
};

#endif // SCREEN1VIEW_HPP
