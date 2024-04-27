import numpy as np
# from sklearn.manifold import TSNE # for t-SNE
import pandas as pd
import plotly.express as px

data_path = "data/TSNE_train_embeddings_clusters.csv"
embeddings_path = "data/train_embeddings_tsne.csv"

data = pd.read_csv(data_path)
embeddings = pd.read_csv(embeddings_path)
alfabet = {0:"A", 1:"B", 2:"C", 3:"D", 4:"C", 5:"E", 6:"F",
           7:"G", 8:"H", 9:"I", 10:"J", 11:"K", 12:"L", 13:"M",
           14:"N", 15:"O", 16:"P", 17:"Q", 18:"R", 19:"S", 20:"T",
           21:"U", 22:"V", 23:"W", 24:"X", 25:"Y", 26:"Z"}

data['x'] = embeddings['x']
data['y'] = embeddings['y']
data['cluster'] = data['cluster'].apply(lambda x: alfabet[x])

fig = px.scatter(data, x='x', y='y', color='cluster', template='plotly_dark')
fig.show()
