
#ifndef GLOBALLABEL_HPP_
#define GLOBALLABEL_HPP_

#include <vector>
#include <string>
using namespace std;

class GLabel {
private:
	int counter;
	GLabel();
public:
	static GLabel* Init();
	string genGLabel();
};

#endif /* GLOBALLABEL_HPP_ */
