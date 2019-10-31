import keras
import numpy as np

from keras.models import Sequential
from keras.layers import Dense, Activation

model = Sequential()
model.add(Dense(8,input_dim=2))
model.add(Activation('sigmoid'))
model.add(Dense(1))
model.add(Activation('sigmoid'))

sgd = keras.optimizers.SGD(lr=0.1)

X = np.array([[0,0],[0,1],[1,0],[1,1]])
y = np.array([[0],[1],[1],[0]])

model.compile(loss='binary_crossentropy',optimizer=sgd)
model.fit(X,y,verbose=1,batch_size=2,epochs=10000)

print(model.predict(X))
