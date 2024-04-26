import pandas as pd
import numpy as np
from llama_index.embeddings.ollama import OllamaEmbedding
import ollama

file_path = "data/reddit_comments_train.csv"
content = pd.read_csv(file_path)['body'].to_list()[:100]


ollama_embedding = OllamaEmbedding(
    model_name="all-minilm",
    base_url="http://localhost:11434",
    ollama_additional_kwargs={"mirostat": 0},
)

pass_embedding = ollama_embedding.get_text_embedding_batch(
    content, show_progress=True)

# query_embedding = ollama_embedding.get_query_embedding("Where is blue?")
# print(query_embedding)
out_file = "data/reddit_comments_train_embeddings.npy"
np.save(out_file, pass_embedding)