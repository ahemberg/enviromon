import datetime
import matplotlib.pyplot as plt
import numpy as np

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


def read_log(filename):
    with open(filename, 'r') as datalog:
        lines = [line.split(';') for line in datalog.readlines()]
    return lines


def parse_data(raw):
    return [parse_row(row) for row in raw]


def parse_row(row):
    return {
        "timestamp": datetime.datetime.utcfromtimestamp(int(row[0].strip())),
        "temperature": float(row[1].strip()),
        "relhumidity": float(row[2].strip()),
        "pressure": float(row[3].strip()),
        "battery_voltage": float(row[4].strip()),
    }



# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    data = read_log('datalog202109092.csv')
    parsed = parse_data(data)
    [print(a) for a in parsed]

    # Plot
    x = [time['timestamp'] for time in parsed]
    fig, axs = plt.subplots(4, sharex=True)
    fig.suptitle('Sensor data')
    axs[0].plot(x, [meas['temperature'] for meas in parsed])
    axs[1].plot(x, [meas['relhumidity'] for meas in parsed])
    axs[2].plot(x, [meas['pressure'] for meas in parsed])
    axs[3].plot(x, [meas['battery_voltage'] for meas in parsed])
    fig.autofmt_xdate()
    a = [p for p in parsed if p['timestamp'].year == 2015]
    plt.show()

    plt.hist([meas['temperature'] for meas in parsed], 100)
    plt.show()
    plt.hist([meas['relhumidity'] for meas in parsed], 20)
    plt.show()
    plt.hist([meas['pressure'] for meas in parsed], 100)
    plt.show()


# See PyCharm help at https://www.jetbrains.com/help/pycharm/
