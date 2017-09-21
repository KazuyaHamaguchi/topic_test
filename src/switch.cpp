#include "ros/ros.h"
#include "topic_test/adder.h"
#include <pigpiod_if2.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "switch");
	ros::NodeHandle nh;

	ros::Publisher switch_pub = nh.advertise<topic_test::adder>("switch_input", 1000);

	ros::Rate loop_rate(10);

	topic_test::adder msg;

	int pi = pigpio_start(0, 0);
	set_pull_up_down(pi, 22, PI_PUD_DOWN);

	int count = 0, flag = 0;	//flagはスイッチのカウント用フラグ
	
	while(ros::ok())
	{
		if(gpio_read(pi, 22) == 1)
		{
			if(flag == 0)
			{
				flag = 1;
				count ++;
				msg.switch_count = count;
				switch_pub.publish(msg);
				printf("switch_count = %d \n", msg.switch_count);
				ros::spinOnce();
				loop_rate.sleep();
			}
			else;
		}
		else
		{
			if(flag == 1)
			{
				flag = 0;
			}
			else;
		}
	}
	gpio_write(pi, 23, 0);	//switchノードが終了したら，LEDを消灯する
	pigpio_stop(pi);
	return 0;
}
