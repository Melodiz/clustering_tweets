import numpy as np

#read the embeddings
PATH = "data/reddit_comments_train_embeddings.npy"
embeddings = np.load(PATH)
print(len(embeddings))
print(embeddings[0])
