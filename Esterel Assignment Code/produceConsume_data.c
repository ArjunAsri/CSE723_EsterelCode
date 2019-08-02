#include<stdio.h>
#include<stdlib.h>
#include "produceConsume.h"
#define SIZE 5

int cq[SIZE];
int front=0;
int rear=0;
int cnt=0;

int outCount(){
  return cnt;
}

void send(int data){
	adding(data);
}

void adding(unsigned int data){
	if(cnt!=SIZE){
		cq[rear]=data;
		rear = (rear +1) % SIZE;
		++cnt;
	}
}

void recv1(char** data){
	int tmp;
	tmp = remov();
	if(tmp != -1)
		sprintf(&data[0],"consumed %d",tmp);
	else
		sprintf(&data[0],"consumed nothing");
}

int remov(void){
	int val;
	if(cnt!=0){
		val=cq[front];
		front = (front+1) % SIZE;
		cnt--;
		return val;
	}else
		return -1;

}



#include <stdbool.h>

/*
DESCRIPTION: Saturate the throttle command to limit the acceleration.
PARAMETERS: throttleIn - throttle input
            saturate - true if saturated, false otherwise
RETURNS: throttle output (ThrottleCmd)
*/
float saturateThrottle(float throttleIn, int saturate)
{
	static const float THROTTLESATMAX = 45.0;
	if (throttleIn > THROTTLESATMAX) {
		saturate = true;
		return THROTTLESATMAX;
	}
	else if (throttleIn < 0) {
		saturate = true;
		return 0;
	}
	else {
		saturate = false;
		return throttleIn;
	}
}

/*
DESCRIPTION: Saturate the throttle command to limit the acceleration.
PARAMETERS: isGoingOn - true if the cruise control has just gone into the ON state 
                        from another state; false otherwise
            saturate - true if saturated, false otherwise
RETURNS: throttle output (ThrottleCmd)
*/
float regulateThrottle(int isGoingOn, float cruiseSpeed, float vehicleSpeed)
{
	static const float KP = 8.113;
	static const float KI = 0.5;
	static bool saturate = true;
	static float iterm = 0;
	
	if (isGoingOn) {
		iterm = 0;	// reset the integral action
		saturate = true;	
	}
	float error = cruiseSpeed - vehicleSpeed;
	float proportionalAction = error * KP;
	if (saturate)
		error = 0;	// integral action is hold when command is saturated
	iterm = iterm + error;
	float integralAction = KI * iterm;
	return saturateThrottle(proportionalAction + integralAction, &saturate);
}
