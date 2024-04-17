import pandas as pd
import numpy as np
PATH = "anon_disorder_tweets.csv"
data = pd.read_csv(PATH)
print(data.shape)