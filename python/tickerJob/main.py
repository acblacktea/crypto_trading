import sys

sys.path.append("./build/src")
import trading

if __name__ == "__main__":
    queue = trading.mmapQueueV2(
        "./data/mmap/event_queue_python_collect_data", 1024 * 1024 * 1024
    )
    while True:
        ticker = queue.pop()
        print(ticker)
