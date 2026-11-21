import requests
import pandas as pd
import numpy as np
from datetime import date, timedelta

# ==========================================
# CONFIGURATION: TWO OPPOSITE CORNER POINTS
# ==========================================

LAT1, LON1 = 28.19, 89.01
LAT2, LON2 = 26.59, 87.74

GRID_SIZE = 3  # 3 x 3 = 9 locations

END_DATE = date.today() - timedelta(days=5)
START_DATE = END_DATE - timedelta(days=6)

# ==========================================
# GENERATE GRID LOCATIONS
# ==========================================

latitudes = np.linspace(min(LAT1, LAT2), max(LAT1, LAT2), GRID_SIZE)
longitudes = np.linspace(min(LON1, LON2), max(LON1, LON2), GRID_SIZE)

locations = [
    (lat, lon)
    for lat in latitudes
    for lon in longitudes
]

# ==========================================
# DOWNLOAD TEMPERATURE AND HUMIDITY DATA
# ==========================================

url = "https://archive-api.open-meteo.com/v1/archive"
dataframes = []

for i, (lat, lon) in enumerate(locations, start=1):

    params = {
        "latitude": float(lat),
        "longitude": float(lon),
        "start_date": START_DATE.isoformat(),
        "end_date": END_DATE.isoformat(),
        "hourly": "temperature_2m,relative_humidity_2m",
        "timezone": "auto"
    }

    response = requests.get(url, params=params, timeout=60)
    response.raise_for_status()
    data = response.json()

    df_location = pd.DataFrame({
        "Time": data["hourly"]["time"],
        "Temperature_C": data["hourly"]["temperature_2m"],
        "Humidity_Percent": data["hourly"]["relative_humidity_2m"]
    })

    df_location["Latitude"] = lat
    df_location["Longitude"] = lon

    dataframes.append(df_location)

# ==========================================
# COMBINE DATA AND EXPORT CSV
# ==========================================

df = pd.concat(dataframes, ignore_index=True)

df["Time"] = pd.to_datetime(df["Time"])
df = df.sort_values(["Time", "Location_ID"]).reset_index(drop=True)

filename = "temperature_humidity_iot.csv"
df.to_csv(filename, index=False)

print("CSV created successfully!")
print("Dataset shape:", df.shape)
print(df.head())
