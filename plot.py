import matplotlib.pyplot as plt

with open('datasets\\2D_data_10000.csv') as fp:
    lines = fp.readlines()
    data = [line.strip().split(',') for line in lines]
    x_c = []
    y_c = []
    for el in data:
        x, y = el
        x_c.append(float(x))  # Convert x to float
        y_c.append(float(y))  # Convert y to float
    plt.scatter(x_c, y_c)
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.title('MeanShift Clustering Result')
    plt.show()
