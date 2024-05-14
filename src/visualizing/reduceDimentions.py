from sklearn.manifold import TSNE  # for t-SNE
import pandas as pd
import numpy as np
import os
from pathlib import Path


def from_npy_to_npy(filepath):
    data = np.load(filepath, allow_pickle=True)
    print('data read from:', filepath)
    result = TSNE(n_components=2, learning_rate='auto',
                  init='random', perplexity=3).fit_transform(data)
    print('result shape: ', result.shape)
    output_file = os.path.join(dir, 't-SNE_projected')  # output file name

    dir = Path(filepath).parent
    np.save(output_file, result)  # save to file path as npy file
    print('result saved to: ', output_file)


def from_npy_to_csv(filepath):
    data = np.load(filepath, allow_pickle=True)
    print('data read from: ', filepath)
    result = TSNE(n_components=2, learning_rate='auto',
                  init='random', perplexity=3).fit_transform(data)

    dir = Path(filepath).parent
    output_file = os.path.join(dir, 't-SNE_projected.csv')  # output file name
    # save to file path as csv file
    pd.DataFrame(result, columns=['x', 'y']).to_csv(output_file, index=False)
    print('result saved to: ', output_file)


def from_npy_return_list(filepath):
    data = np.load(filepath, allow_pickle=True)
    result = TSNE(n_components=2, learning_rate='auto',
                  init='random', perplexity=3).fit_transform(data)
    return result


def from_list_return_list(data):
    result = TSNE(n_components=2, learning_rate='auto',
                  init='random', perplexity=3).fit_transform(data)
    return result


if __name__ == "__main__":
    from time import time
    start = time()
    from_npy_to_csv(filepath='data/train_embeddings.npy')
    end = time()
    print(f'time required: {end-start} seconds')
