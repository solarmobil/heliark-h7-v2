#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}
void Screen1View::rpm(int data)
{
	float speed=60.5;


	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", speed);
	textArea2.resizeToCurrentTextWithAlignment();
	int textWidth = textArea2.getTextWidth();
	int x = (480 - textWidth) / 2;
	textArea2.setX(x);
	textArea2.invalidate();
	imageProgress1.setValue(data);
	imageProgress1.invalidate();
	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%d", data);
	int textWidth1 = textArea3.getTextWidth();
    int x1 = ((480 - textWidth1) / 2)-20;
	textArea3.setX(x1);
	textArea3.invalidate();




}
void Screen1View::speed(int data)
{



	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", data);
	textArea2.resizeToCurrentTextWithAlignment();
	int textWidth = textArea2.getTextWidth();
	int x = (480 - textWidth) / 2;
	textArea2.setX(x);
	textArea2.invalidate();



}
void Screen1View::soc(int data)
{



	imageProgress2.setValue(data);
	imageProgress2.invalidate();
	Unicode::snprintf(textArea4Buffer, TEXTAREA4_SIZE, "%d", data);
	textArea4.invalidate();



}
void Screen1View::battery1(battery_t data)
{
	Unicode::snprintf(textArea5Buffer, TEXTAREA5_SIZE, "%d",data.temp1);
	textArea5.invalidate();
	Unicode::snprintf(textArea5_1Buffer, TEXTAREA5_1_SIZE, "%d",data.temp2);
    textArea5_1.invalidate();
	Unicode::snprintf(textArea6Buffer, TEXTAREA6_SIZE, "%d",data.voltage);
	textArea6.invalidate();






}
void Screen1View::motor(motor_t data)
{


	Unicode::snprintf(textArea7Buffer, TEXTAREA5_SIZE, "%d",data.current);
	textArea7.invalidate();
	Unicode::snprintf(textArea7_1Buffer, TEXTAREA6_SIZE, "%d",data.temp);
	textArea7_1.invalidate();
	Unicode::snprintf(textArea6_1Buffer, TEXTAREA6_1_SIZE, "%d",data.voltage);
	textArea6_1.invalidate();
	Unicode::snprintf(textArea5_1_1Buffer,TEXTAREA5_1_1_SIZE , "%d",data.cont_temp);
		textArea5_1_1.invalidate();



}
void Screen1View::target(target_t data)
{


	Unicode::snprintf(textArea8Buffer, TEXTAREA5_SIZE, "%d",data.range);
	int textWidth = textArea8.getTextWidth();
		int x = (480 - textWidth) / 2;
		textArea8.setX(x);

	textArea8.invalidate();
	Unicode::snprintf(textArea8_1Buffer, TEXTAREA6_SIZE, "%d",data.speed);
	int textWidth1 = textArea8_1.getTextWidth();
			int x1 = (480 - textWidth1) / 2;
			textArea8_1.setX(x1);
	textArea8_1.invalidate();


}

void Screen1View::time(char *data)
{
	int hour   = (data[0] - '0') * 10 + (data[1] - '0')+5;
	if(hour>23)
		hour-=24;
	    int minute = (data[2] - '0') * 10 + (data[3] - '0')+30;
	    if(minute>59){
	    	minute-=60;
	    	hour+=1;
	    }

	    int second = (data[4] - '0') * 10 + (data[5] - '0');

	    Unicode::snprintf(textArea9Buffer,     TEXTAREA9_SIZE,     "%02d", hour);
	    Unicode::snprintf(textArea9_1Buffer,   TEXTAREA9_1_SIZE,   "%02d", minute);
	    Unicode::snprintf(textArea9_1_1Buffer, TEXTAREA9_1_1_SIZE, "%02d", second);

	    textArea9.invalidate();
	    textArea9_1.invalidate();
	    textArea9_1_1.invalidate();

}
void Screen1View::gpsspeed(int data)
{
	    Unicode::snprintf(textArea10Buffer, TEXTAREA10_SIZE, "%d", data);
		textArea10.resizeToCurrentTextWithAlignment();
		int textWidth = textArea10.getTextWidth();
		int x = (480 - textWidth) / 2;
		textArea10.setX(x);
		textArea10.invalidate();

}
