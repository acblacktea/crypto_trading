#pragma once
class binanceClient {
public:
    auto getTickData();
    auto getCandleSticks();
    auto placeOrders();
    auto cancelOrders();
};