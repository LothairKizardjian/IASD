import os
import sys

import keras
import numpy as np
import matplotlib.pyplot as plt

from keras.utils import to_categorical
from keras.models import *
from keras.layers.core import Dense, Activation
from keras.optimizers import SGD

from keras.datasets import mnist

print("Loading train and test sets ...")
(train_images, train_labels),(test_images,test_labels) = mnist.load_data()

# the input data are images of 28*28 pixels gray scalled (0 to 255) so we need to shrink it to floats

x_train = train_images.reshape((60000,28*28)).astype(float)/255
y_train = to_categorical(train_labels.astype(float))

x_test  = test_images.reshape((10000,28*28)).astype(float)/255
y_test  = to_categorical(test_labels.astype(float))

def save(model):
    model_json = model.to_json()
    with open('model.json','w') as json_file:
        json_file.write(model_json)
        model.save_weights("model.h5")
        print("Saved model to disk")

def create_model():
    model = Sequential()
    model.add(Dense(512,input_shape=(28*28,)))
    model.add(Activation('relu'))
    model.add(Dense(10))
    model.add(Activation('softmax'))

    return model

def compile(model):
    model.compile(loss='categorical_crossentropy',optimizer='rmsprop', metrics=['accuracy'])

def train(model):
    compile(model)
    model.fit(x_train,y_train,verbose=1,batch_size=32,epochs=10)

    save(model)

def load():
    json_file = open('model.json','r')
    loaded_model_json = json_file.read()
    json_file.close()
    loaded_model = model_from_json(loaded_model_json)
    loaded_model.load_weights('model.h5')
    
    print("loaded model from disk")
    return loaded_model

def main():    
    if(os.path.isfile('model.json')):
        model = load()
        compile(model)
    else:
        model = create_model()
        train(model)

    test_loss,test_acc = model.evaluate(x_test,y_test)
    print('test acc :',test_acc)

    #plt.imshow(test_images[0])
    #print(model.predict_classes(x_test[0]))
    
main()

