Q2. Write a Python function that simulates a simple MP Neuron.

The function should take a list
of non-binary inputs (age, salary, number of family members) and predict whether he/she
will buy the house or not (binary output).

It should return 1 if the sum of the inputs is
greater than the threshold, and 0 otherwise.

Generate 500 records (synthetic data) and use
70% of dataset to train the MP-Neuron model.

Compute the test accuracy of the model on
the test (30%) dataset.

import pandas as pd

## Generating Data



## Importing Data



file_path = '/content/sample_data/housing_data.csv'
daf = pd.read_csv(file_path)
df = df.rename(columns={'num_family_members': 'family_members', 'will_buy_house': 'buy_house'})
df.sample(10)

df_norm = df.mean()/df.std()

data = df_norm.drop('buy_house')
target = df_norm['buy_house']
target

## Train Test Split

from sklearn.model_selection import train_test_split

data_train, data_test, target_train, target_test = train_test_split(data, target, random_state = 1)
print(data_train.shape, data_test.shape, target_train.shape, target_test.shape)

## Binarization of Inputs

data

import matplotlib.pyplot as plt
import numpy as np

plt.plot(data_train.T, "*")
plt.xticks(rotation='vertical')
plt.show()

columns_to_plot = ['age', 'salary', 'family_members']

for col in columns_to_plot:
    plt.figure(figsize=(8, 5))
    plt.hist(df[col], bins=20, edgecolor='black')
    plt.title(f'Distribution of {col.replace("_", " ").title()}')
    plt.xlabel(col.replace("_", " ").title())
    plt.ylabel('Frequency')
    plt.grid(axis='y', alpha=0.75)
    plt.show()