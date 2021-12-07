from os import write
import serial
import time
import csv

arduinoPort = "COM6"
arduinoBaud = 9600
serialPipe = serial.Serial(arduinoPort, arduinoBaud)
print("Connected to Arduino port " + arduinoPort)

csvFile="temperature.csv"

with open(csvFile, "w", newline='') as file:
  print("CSV file was opened")
  aWriter = csv.writer(file)

  while (True):
    collectData = str(serialPipe.readline())[2:-5]
    # processedData = collectData[2:-5]
    processedData = collectData.replace(".", ",")
    outputTime = time.strftime("%d %b %Y %H:%M", time.localtime())
    parameters = [processedData, outputTime]

    print(processedData + "\t" + outputTime)
    aWriter.writerow(parameters)
