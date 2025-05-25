from __future__ import absolute_import, division, print_function, unicode_literals
import datetime
import backtrader as bt
import matplotlib


class TestStrategy(bt.Strategy):
    params = (("exitbars", 5), ("maperiod", 15))

    def log(self, txt, dt=None):
        """Logging function for this strategy"""
        dt = self.datas[0].datetime.date(0)
        time = self.datas[0].datetime.time(0)
        print("%s, %s, %s" % (dt.isoformat(), time.isoformat(), txt))

    def __init__(self):
        # Keep a reference to the "close" line in the data[0] dataseries
        self.dataclose = self.datas[0].close
        self.order = None
        self.buyprice = None
        self.buycomm = None
        self.sma = bt.indicators.SimpleMovingAverage(
            self.datas[0], period=self.params.maperiod
        )

    def notify_order(self, order):
        if order.status in [order.Submitted, order.Accepted]:
            return

        if order.status in [order.Completed]:
            if order.isbuy():
                self.buyprice = order.executed.price
                self.buycomm = order.executed.comm
            self.bar_executed = len(self)

        self.order = None

    def notify_trade(self, trade):
        if not trade.isclosed:
            return

    def next(self):
        if self.order:
            return

        if not self.position:
            if self.dataclose[0] > self.sma[0]:
                self.order = self.buy()
        else:
            if self.dataclose[0] < self.sma[0]:
                self.order = self.sell()

    def stop(self):
        self.log(
            "(MA Period %2d) Ending Value %.2f"
            % (self.params.maperiod, self.broker.getvalue())
        )


if __name__ == "__main__":
    cerebro = bt.Cerebro()
    cerebro.optstrategy(TestStrategy, maperiod=range(10, 31))

    data = bt.feeds.GenericCSVData(
        dataname="kline.csv",
        fromdate=datetime.datetime(2025, 1, 1),
        todate=datetime.datetime(2025, 12, 31),
        nullvalue=0.0,
        timeframe=bt.TimeFrame.Minutes,
        dtformat=("%Y-%m-%d"),
        tmformat=("%H:%M:%S"),
        datetime=0,
        time=1,
        high=2,
        low=3,
        open=4,
        close=5,
        volume=6,
        openinterest=-1,
    )

    cerebro.broker.setcash(1000000.0)
    cerebro.broker.setcommission(commission=0.0005)
    cerebro.addsizer(bt.sizers.FixedSize, stake=10)
    cerebro.adddata(data)
    print("starting portfolio value: %.2f" % cerebro.broker.getvalue())
    cerebro.run()
    print("Final portfolio value: %.2f" % cerebro.broker.getvalue())
    print(matplotlib.get_backend())
    # cerebro.plot()
