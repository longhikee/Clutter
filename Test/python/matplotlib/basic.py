# 导入 matplotlib 的所有内容（nympy 可以用 np 这个名字来使用）
from pylab import *

# 创建一个 8 * 6 点（point）的图，并设置分辨率为 80
figure(figsize=(8,5), dpi=80)


# 创建一个新的 1 * 1 的子图，接下来的图样绘制在其中的第 1 块（也是唯一的一块）
subplot(1,1,1)

X = np.linspace(-np.pi, np.pi, 256,endpoint=True)
C,S = np.cos(X), np.sin(X)

# 绘制余弦曲线，使用蓝色的、连续的、宽度为 1 （像素）的线条
plot(X, C, color="blue", linewidth=2.0, linestyle="-")

# 绘制正弦曲线，使用绿色的、连续的、宽度为 1 （像素）的线条
plot(X, S, color="green", linewidth=1.0, linestyle="None")

# 设置横轴的上下限
xlim(-4.0,4.0)

# 设置纵轴的上下限
ylim(-1.0,1.0)

# 设置横轴记号
#xticks(np.linspace(-4,4,9,endpoint=True))
xticks([-np.pi, -np.pi/2, 0, np.pi/2, np.pi],
       [r'$-\pi$', r'$-\pi/2$', r'$0$', r'$+\pi/2$', r'$+\pi$'])

# 设置纵轴记号
#yticks(np.linspace(-1,1,5,endpoint=True))
yticks([-1, 0, +1],
       [r'$-1$', r'$0$', r'$+1$'])

#优化边界
Y = C
xmin, xmax = X.min(), X.max()
ymin, ymax = Y.min(), Y.max()

xd = (xmax - xmin) * 0.2
yd = (ymax - ymin) * 0.2
xlim(xmin - xd, xmax + xd)
ylim(ymin - yd, ymax + yd)


#中置 Spines
ax = gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))

#添加图例
plot(X, C, color="blue", linewidth=2.5, linestyle="-", label="cosine")
plot(X, S, color="green", linewidth=2.5, linestyle="dashed", label="sine")
legend(loc='upper left')
#legend(loc='lower left')

#注释
t = 2 * np.pi/3
plot([t,t],[0,np.cos(t)], color ='blue', linewidth=2.5, linestyle="--")
scatter([t,],[np.cos(t),], 50, color ='blue')
annotate(r'$\cos(\frac{2\pi}{3})=-\frac{1}{2}$',
         xy=(t, np.cos(t)), xycoords='data',
         xytext=(-90, -50), textcoords='offset points', fontsize=16,
         arrowprops=dict(arrowstyle="->", connectionstyle="arc3,rad=.2"))

#遮挡透明化
for label in ax.get_xticklabels() + ax.get_yticklabels():
    label.set_fontsize(16)
    label.set_bbox(dict(facecolor='white', edgecolor='None', alpha=0.65 ))

#在屏幕上显示
show()
