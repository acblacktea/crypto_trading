build:
	/usr/bin/cmake --build ./build --config Debug --target all -j 2 --

run_cpp_trading:
	./build/src/crypto_trading_cpp_trading
run_python_trading:
	./build/src/crypto_trading_python_trading
run_collect_data_cron_job_receiver:
	./build/src/crypto_trading_ticker_collect_receiver

run_collect_data_cron_job_consumer:
	python ./python/tickerJob/main.py
	