
import sys
#import Worker

def main():
    # perform what I want to do
    return 0

def processDataFromCsv(filename):
    print("Processing data from Csv... --> " + filename)
    return 0

def collectDataFromSerial():
    print("Collecting data from Serial ...")
    return 0

if __name__ == "__main__":
    if (len(sys.argv) < 2):
        print("\n*Lack of parameters. You can use the following options:")
        print("\n   processCsv\n   readSerial")
    elif (sys.argv[1] == "processCsv"):
        if (len(sys.argv) == 2):
            print("\n*Csv file is missing, please append the name after processCsv option")
        else:
            processDataFromCsv(sys.argv[2])
    elif (sys.argv[1] == "readSerial"):
        collectDataFromSerial()
    else:
        print("\n*Option not valid, please use these ones:")
        print("\n   processCsv\n   readSerial")

