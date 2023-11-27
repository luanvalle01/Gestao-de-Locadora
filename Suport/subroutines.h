#include "constructors.h"
#include "moviesSubroutines.h"
#include "clientsSubroutines.h"

int state0(char input, Frame *frame){

	updateFrame(frame, &input);
	showFrame(frame);
	
	if(input == 10){
		switch(frame->optionSelect){
			case 0:
				return 1;
				break;
			case 1:
				return 2;
				break;
			case 2:
				//state = 3;
				break;
			default:
				return -3;
				break;
		}
	}
	
	return 0;
}

int stateSucess(char input, Frame *frame, int lastState){

	updateFrame(frame, &input);
	showFrame(frame);

	if(input == 10)
		return 0;
}

int stateInvalid(char input, Frame *frame, int lastState){

	updateFrame(frame, &input);
	showFrame(frame);
	
	if(input == 10){
		switch(frame->optionSelect){
			case 0:
				return lastState;
				break;
			case 1:
				if(lastState > 0 && lastState < 200)
					return 1;
				break;
		}
	}
	
	return -1;
}
