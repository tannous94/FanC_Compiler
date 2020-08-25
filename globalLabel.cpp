#include "globalLabel.hpp"
#include <assert.h>
#include <sstream>



GLabel* GlobalLabel = 0;

GLabel* GLabel::Init(){
    if(!GlobalLabel)
    	GlobalLabel = new GLabel();
    return GlobalLabel;
}

GLabel::GLabel() : counter(0) {
	
}

string GLabel::genGLabel() {
	counter++;
	stringstream label;
	label << "gLabel_";
	label << counter;
	string ret(label.str());
	label << ":";
	return ret;
}
