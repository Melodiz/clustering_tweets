import pandas as pd
import numpy as np
from llama_index.embeddings.ollama import OllamaEmbedding
import ollama
from pathlib import Path
import os

def get_query_embedding(query):
    ollama_embedding = OllamaEmbedding(
        model_name="all-minilm",
        base_url="http://localhost:11434",
        ollama_additional_kwargs={"mirostat": 0},
    )
    query_embedding = ollama_embedding.get_query_embedding(query)
    return query_embedding

def transform_banch_of_text_direct(text_batch):
    ollama_embedding = OllamaEmbedding(
        model_name="all-minilm",
        base_url="http://localhost:11434",
        ollama_additional_kwargs={"mirostat": 0},
    )
    pass_embedding = ollama_embedding.get_text_embedding_batch(
    text_batch, show_progress=True)
    return pass_embedding


def transform_banch_of_text_csv(file_path):
    directory = Path(file_path).parent

    content = pd.read_csv(file_path)['body'].to_list()

    ollama_embedding = OllamaEmbedding(
        model_name="all-minilm",
        base_url="http://localhost:11434",
        ollama_additional_kwargs={"mirostat": 0},
    )
    pass_embedding = ollama_embedding.get_text_embedding_batch(
        content, show_progress=True)

    # save to file
    dir = Path(file_path).parent
    output_file = os.path.join(dir,'train_embeddings')

    np.save(output_file, pass_embedding)
    print('result saved to: ', output_file)
    

def transform_banch_of_text_puretxt(file_path):
    content = []
    with open(file_path) as f:
        for line in f:
            content.append(line)

    ollama_embedding = OllamaEmbedding(
        model_name="all-minilm",
        base_url="http://localhost:11434",
        ollama_additional_kwargs={"mirostat": 0},
    )
    pass_embedding = ollama_embedding.get_text_embedding_batch(
        content, show_progress=True)


    # save to file
    dir = Path(file_path).parent
    output_file = os.path.join(dir,'embedded_data')

    np.save(output_file, pass_embedding)
    print('result saved to: ', output_file)



if __name__ == "__main__":
    transform_banch_of_text_csv(file_path='embedings_core/data/reddit_comments_train.csv')