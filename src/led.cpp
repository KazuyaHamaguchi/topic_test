#include "ros/ros.h"
#include "topic_test/adder.h"
#include <pigpiod_if2.h>

void led(const topic_test::adder msg)
{
	int pi = pigpio_start(0, 0);
        set_mode(pi, 23, PI_OUTPUT);
	
	if(msg.switch_count % 2 == 1)
	{
		gpio_write(pi, 23, 1);
		printf("switch_count = %d  LED = ON\n", msg.switch_count);
	}
	else
	{
		gpio_write(pi, 23, 0);
                printf("switch_count = %d  LED = OFF\n", msg.switch_count);
	}
	pigpio_stop(pi);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "led");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("switch_input", 1000, led);

	ros::spin();

	return 0;
}
