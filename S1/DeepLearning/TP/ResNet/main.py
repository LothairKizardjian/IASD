import tensorflow

from tensorflow.keras.datasets import cifar10
from tensorflow.keras import layers
from tensorflow.keras.utils import to_categorical

def get_data():
    (x_train, y_train), (x_test, y_test) = cifar10.load_data()
    x_train = x_train.reshape(x_train.shape[0],32,32,3)/255
    y_train = to_categorical(y_train)
    x_test = x_test.reshape(x_test.shape[0],32,32,3)/255
    y_test = to_categorical(y_test)

    return (x_train, y_train), (x_test, y_test)

def get_cnn(input_shape):    
    input = layers.Input(input_shape)
    x = layers.Conv2D(32, 1, activation='relu', padding='same')(input)
    x = layers.Conv2D(32,(3,3),activation='relu',padding='same')(x)
    x = layers.Flatten()(x)
    x = layers.Dense(128,activation='relu')(x)
    x = layers.Dense(10,activation='softmax')(x)
    
    model = tensorflow.keras.models.Model(inputs=input,outputs=x)
    return model
    
def get_resnet(input_shape):
    input = layers.Input(input_shape)
    x = layers.Conv2D(32, 1, activation='relu', padding='same')(input)
    ident = x
    x = layers.Conv2D(32,(3,3),activation='relu',padding='same')(x)
    x = layers.add([ident,x])
    x = layers.Flatten()(x)
    x = layers.Dense(128,activation='relu')(x)
    x = layers.Dense(10,activation='softmax')(x)
    
    model = tensorflow.keras.models.Model(inputs=input,outputs=x)
    return model

input_shape = (32,32,3)
(x_train, y_train), (x_test, y_test) = get_data()

conv_net = get_cnn(input_shape)
conv_net.compile(optimizer='Adam',loss='categorical_crossentropy',metrics=['accuracy'])
conv_net.fit(x_train,y_train,verbose=1,batch_size=128,epochs=10,validation_data=(x_test,y_test))

# res_net = get_resnet(input_shape)
res_net = tensorflow.keras.applications.ResNet50()
res_net.compile(optimizer='Adam',loss='categorical_crossentropy',metrics=['accuracy'])
res_net.fit(x_train,y_train,verbose=1,batch_size=128,epochs=10,validation_data=(x_test,y_test))



