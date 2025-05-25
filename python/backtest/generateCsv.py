import json
import csv
from datetime import datetime
import matplotlib

matplotlib.use("Agg")

if __name__ == "__main__":
    json_objects = []

    file_path = "./test.txt"
    with open(file_path, "r", encoding="utf-8") as file:
        for line_number, line in enumerate(file, 1):
            line = line.strip()
            if not line:
                continue  # Skip empty lines

            try:
                json_obj = json.loads(line)
                json_objects.append(json_obj)
            except json.JSONDecodeError as e:
                print(f"Error parsing line {line_number}: {e}")
                print(
                    f"Problematic line content: {line[:100]}..."
                )  # Show first 100 chars
    data = [["datetime", "time", "high", "low", "open", "close", "volume"]]

    for object in json_objects:
        if object["data"]["s"] != "SOLUSDT":
            continue

        datetimeInt = object["data"]["k"]["t"]
        print(datetimeInt)
        dt = datetime.fromtimestamp(datetimeInt / 1000)
        dateStr = dt.strftime("%Y-%m-%d")
        timeStr = dt.strftime("%H:%M:%S")
        high = object["data"]["k"]["h"]
        low = object["data"]["k"]["l"]
        op = object["data"]["k"]["o"]
        close = object["data"]["k"]["c"]
        volume = object["data"]["k"]["v"]
        data.append([dateStr, timeStr, high, low, op, close, volume])

    with open("kline.csv", "w", encoding="utf-8", newline="") as file:
        writer = csv.writer(file)
        writer.writerows(data)
