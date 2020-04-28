#import matplotlib.pyplot as pyp
import numpy as np
#data = np.loadtxt("D:\Projects\C++\Modelirovanie\Lab6\Lab6\Track.txt")
#pyp.plot(data[:, 0], data[:, 1])
#pyp.show()

# -*- coding: utf-8 -*- 
import matplotlib.pyplot as plt 
import pylab 
#from mpl_toolkits.mplot3d import Axes3D 
def makeData():
# Формирование сетки 
    X = np.arange(5, 45, 0.1) 
    Y = np.arange(-5, 40, 0.1) 
    X, Y = np.meshgrid(X, Y) 
    Z =-(X*X/3)-(X*Y/6)+(127*X/6)-(Y*Y/3)+(91*Y/6)-(239/2) 
    # Z = (X-2)**2+(Y-9)**2+X*Y 
    return X, Y, Z 

if __name__ == '__main__': 
    x, y, z = makeData() 
    fig = pylab.figure("Линии_уровня") 
    #axes = Axes3D(fig) 
    data=np.loadtxt ("D:\Projects\C++\Modelirovanie\Lab6\Lab6\Track.txt") 
    X=data[:,0] 
    Y=data[:,1] 
    k=len(X) 
    X1=[X[k-1]] 
    Y1=[Y[k-1]] 
    #axes.plot_surface(x, y, z) 
    #fig = pylab.figure("Линии_уровня") 
    title="f(x1,x2) = -(x1*x1/3)-(x1*x2/6)+(127*x1/6)-(x2*x2/3)+(91*x2/6)-(239/2)"
    plt.title(title) 
    plt.plot(X,Y,"g", linewidth = 2) 
    plt.plot(X1,Y1,"or") 
    plt.xlabel('ось x1') 
    plt.ylabel('ось x2') 
    # Координаты точки, куда будет указывать стрелка 
    selected_x = X1[0] 
    selected_y = Y1[0] 
    
    pylab.rc('font', family = 'verdana') 
    # !!! Словарь задает внешний вид стрелки 
    arrowprops = { 'arrowstyle': '->', } 
    # !!! Добавление аннотации 
    a = np.array ([X[k-1]-4, Y[k-1]-6]) 
    # !!! Добавление аннотации 
    pylab.annotate (u'Точка максимума', xy=(X1[0], Y1[0]), xytext = a, arrowprops = arrowprops) 
    fig.set_figwidth(8) 
    fig.set_figheight(5) 
    pylab.contourf(x, y, z, levels=30) 
    pylab.show()