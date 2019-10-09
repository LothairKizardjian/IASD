import math
import numpy as np

i1, i2 = 0.1,0.5
inputs = [i1,i2]

w1, w2, w3 = 0.1, 0.3, 0.4
weights= [w1,w2,w3]

net_h1, out_h1, net_o1, out_o1 = 0,0,0,0
nets = [net_h1,net_o1]
outs = [out_h1,out_o1]

target = 0.2

def forward():
    net_h1 = i1*w1 + i2*w2
    out_h1 = 1/(1+math.exp(-net_h1))
    
    net_o1 = out_h1*w3
    out_o1 = 1/(1+math.exp(-net_o1))

    nets[0] = net_h1
    nets[1] = net_o1
    outs[0] = out_h1
    outs[1] = out_o1
    
    return out_o1

def error(predicted, real):
    return (0.5 * ((real - predicted)**2))

prediction = forward()
print(outs[1])
error      = error(prediction,target)

def back_propagation(eta):
    d1 = -(target - outs[1])
    d2 = outs[1] * (1 - outs[1])
    d3 = outs[0]
    d = d1 * d2 * d3

    new_w3 = weights[2] - eta*d
    new_w1 = weights[0] - eta*d1*d2*weights[2]
    new_w2 = weights[1] - eta*d1*d2*weights[2]

def train(t,eta):
    for i in range(t) :
        back_propagation(eta)
        print(error(forward(),target))

train(1000,0.5)
