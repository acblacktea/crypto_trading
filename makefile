build:
	/usr/bin/cmake --build ./build --config release --target all -j 2 --

debug:
	/usr/bin/cmake --build ./build --config debug --target all -j 2 --

run_cpp_trading:
	./build/src/crypto_trading_cpp_trading
run_python_trading:
	./build/src/crypto_trading_python_trading

run_ticker_cpp:
	./build/src/crypto_trading_ticker

run_ticker_python:
	python ./python/tickerJob/main.py
	