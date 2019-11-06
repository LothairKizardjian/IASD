from keras.datasets import mnist,cifar10
from keras.layers import Conv2D
from keras.layers import Dense, Flatten, Dropout, Activation
from keras import regularizers
from keras.utils import to_categorical
from keras.models import Sequential
from keras.layers.pooling import MaxPooling2D
from keras import layers
import keras

# ================================= #
# ============ MNIST ============== #
# ================================= #

def main1():
    (x_train,y_train), (x_test,y_test) = mnist.load_data()
    x_train = x_train.reshape(60000,28,28,1).astype('float32')
    x_test  = x_test.reshape(10000,28,28,1).astype('float32')
    x_train /= 255
    x_test  /= 255
    
    y_train = to_categorical(y_train)
    y_test = to_categorical(y_test)
    
    model = Sequential()
    model.add(Conv2D(32,kernel_size=3,kernel_regularizer=regularizers.l2(0.001),strides=1,padding='valid',activation='relu',input_shape=(28,28,1)))    
    model.add(Dropout(0.3))
    model.add(MaxPooling2D(pool_size=(2,2),strides=2,padding='valid',data_format='channels_last'))
    model.add(Conv2D(64,kernel_size=3,kernel_regularizer=regularizers.l2(0.001),strides=1,padding='valid',activation='relu'))
    model.add(Dropout(0.3))
    model.add(Flatten())
    model.add(Dense(128,activation='relu'))
    model.add(Dropout(0.3))
    model.add(Dense(10,activation='softmax'))
    
    model.compile(loss='categorical_crossentropy',optimizer='adam',metrics=['accuracy'])
    model.fit(x_train,y_train,validation_data=(x_test,y_test),batch_size=128,epochs=10)

# ================================= #
# =========== CIFAR10 ============= #
# ================================= #

def main2():
    (x_train,y_train), (x_test,y_test) = cifar10.load_data()
    x_train = x_train.astype('float32')/255
    x_test  = x_test.astype('float32')/255

    y_train = to_categorical(y_train)
    y_test  = to_categorical(y_test)

    input = keras.layers.Input(shape=(32,32,3))
    x = Conv2D(32,kernel_size=3,strides=1,padding='same')(input)
    x = Conv2D(3 ,kernel_size=3,strides=1,padding='same')(x)
    x = layers.add([input,x])
    x = Activation('relu')(x)
    x = Flatten()(x)
    x = Dropout(0.3)(x)
    x = Dense(128,activation='relu')(x)
    x = Dropout(0.3)(x)
    x = Dense(10,activation='softmax')(x)

    model = keras.models.Model(inputs=input,outputs=x)
    model.compile(loss='categorical_crossentropy',optimizer='adam',metrics=['accuracy'])
    model.fit(x_train,y_train,validation_data=(x_test,y_test),batch_size=256,epochs=20)
    
main2()
    

