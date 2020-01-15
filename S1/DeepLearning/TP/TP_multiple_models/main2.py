import tensorflow.keras as keras
from tensorflow.keras import layers
import numpy as np

input = keras.Input(shape=(19,19,6))
x = layers.Conv2D(32,3,activation='relu')(input)
x = layers.Conv2D(64,3,activation='relu')(x)
x = layers.Conv2D(128,3,activation='relu')(x)
x = layers.Flatten()(x)

value = layers.Dense(1,activation='sigmoid',name='value')(x)
policy= layers.Dense(362,activation='softmax',name='policy')(x)

model = keras.Model(inputs=input,outputs=[value,policy])
model.compile(optimizer=keras.optimizers.RMSprop(1e-3),
              loss={'value':'mse','policy':'sparse_categorical_crossentropy'},
              loss_weights=[0.001,1.],metrics=['accuracy'])

num_tensors= 10000

input_data = np.random.randint(2,size=(num_tensors,19,19,6))
policy_targets = np.random.randint(362,size=(num_tensors))
value_targets = np.random.randint(2,size=(num_tensors))

model.fit(input_data,{'value':value_targets,'policy':policy_targets},epochs=100,batch_size=32)
