#include "bridge.h"

int main()
{
    Bridge bridge;
    bridge.shuffleAndDeal();
    bridge.showHands();
    bridge.conductAuction();
    bridge.play();
    bridge.score();
    return 0;
}
