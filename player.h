#include <string>

using namespace std;

class Player {
    string name;
    float stack;
    int suiteCount [4]; // 0: spade, 1: club, 2: heart, 3: diamond
    
    public:
        Player(string name): name{name}, stack(300.0), suitCount{0,0,0,0} {};
        float getStack();
        float getSuiteCount(int index);
        void addToStack(float amount);
        void addToSuite(int index);
        void removeFromStack(float amount);
        void removeFromSuite(int index);
};

