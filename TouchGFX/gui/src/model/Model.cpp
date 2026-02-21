#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "cmsis_os2.h"
#include "string.h"
extern osMessageQueueId_t myQueue01Handle;
Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if(osMessageQueueGetCount(myQueue01Handle)>0)
	            	{
	            		if(osMessageQueueGet(myQueue01Handle,&r,0,0)==osOK)
	            				{
	            float speed=0.088972*(r->rpm);
	            int sp=int(speed);

				modelListener->rpm(r->rpm);
				modelListener->speed(sp);
				modelListener->soc(r->soc);
				modelListener->battery1(r->battery1);
				modelListener->motor(r->motor);
				modelListener->target(r->target);
				modelListener->time(r->system.time);
				modelListener->gpsspeed(r->system.gps_speed);


	            				}}

}
