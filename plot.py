import matplotlib.pyplot as plt

with open('data.txt') as fp:
    lines = fp.readlines()
    list = [line.strip().split() for line in lines]
    x_c = []
    y_c = []
    for el in list:
        x, y = el
        x_c.append(x)
        y_c.append(y)
    print(x_c)
    plt.scatter(x_c, y_c)
    plt.show()
    
        
    
