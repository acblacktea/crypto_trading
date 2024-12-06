#pragma once
class TradingEngine {
public:
    auto updateTickData();
    auto updateCandleStick();
    auto placeOrder();
    auto executeStrategy();
};