import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

dataset = pd.read_csv("Data.csv")
x = dataset.iloc[:, :-1].values  ## -1 : except last one column, x: independent variable
y = dataset.iloc[:, -1 ].values
# print(x)
# print(y)

## fill empty data
from sklearn.impute import SimpleImputer
imputer = SimpleImputer(missing_values=np.nan, strategy = 'mean')
imputer.fit(x[:, 1:3])
x[:, 1:3] = imputer.transform(x[:, 1:3])
# print(x)


## encoding catogory
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder
ct = ColumnTransformer(transformers=[('encoder', OneHotEncoder(),[0])], remainder='passthrough')
x = np.array(ct.fit_transform(x)) ##conver to numpy array
# print(x)

## encoding depending
from sklearn.preprocessing import LabelEncoder
le = LabelEncoder()
y = le.fit_transform(y)
# print(y)

## feature scaling: avoid some variable to be dominant since its value is large in linear regression.
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
x = sc.fit_transform(x)
# print(x)

from sklearn.model_selection import train_test_split
[x_train, x_test, y_train, y_test] = train_test_split(x, y, test_size=0.2,random_state=0)
print(x_train)
print(x_test)
print(y_train)
print(y_test)