import os
import sys
import keras
import tensorflow as tf
import numpy as np

from keras.utils import *
from keras.models import *
from keras.layers import *
from keras.optimizers import *

from keras.datasets import imdb

(train_data,train_labels),(test_data,test_labels) = imdb.load_data(num_words=10000)

x_train = []
x_test  = []

for review in train_data:
    vector = [0 for x in range(10000)]
    for index in review:
        vector[index]=1
    x_train.append(vector)

for review in test_data:
    vector = [0 for x in range(10000)]
    for index in review:
        vector[index]=1
    x_test.append(vector)

x_train = np.asarray(x_train).astype(float)
x_test  = np.asarray(x_test).astype(float)

y_train = np.asarray(train_labels).astype(float)
y_test  = np.asarray(test_labels).astype(float)

partial_x = x_train[:15000]
partial_y = y_train[:15000]
x_val     = x_train[15000:]
y_val     = y_train[15000:]

def save(model):
    model_json = model.to_json()
    with open('model.json','w') as json_file:
        json_file.write(model_json)
        model.save_weights("model.h5")
        print("Saved model to disk")

def create_model():
    model = Sequential()
    model.add(Dense(32,activation='relu',input_shape=(10000,)))
    model.add(Dense(16,activation='relu'))
    model.add(Dense(8 ,activation='relu'))
    model.add(Dense(1))
    model.add(Activation('sigmoid'))

    return model

def compile(model):
    model.compile(loss='binary_crossentropy',optimizer='rmsprop', metrics=['accuracy'])

def train(model):
    compile(model)
    model.fit(partial_x,partial_y,verbose=1,batch_size=64,epochs=20,validation_data=(x_val,y_val))

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

main()
