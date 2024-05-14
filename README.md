# Short description of the project

## Data

We obtained the data from [Kaggle](https://www.kaggle.com/datasets/pavellexyr/the-reddit-climate-change-dataset). This dataset contains all the posts and comments on Reddit mentioning the terms "climate" and "change" up until 2022-09-01.

## Embedding Logic

To run the model locally, we used Ollama. Due to limited computing power, we utilized the "all-minilm" embedding model. The first 10,000 comments from the initial data were transformed into embeddings using the script in embeddings_code/transformer.py.

```python
ollama_embedding = OllamaEmbedding(
    model_name="all-minilm",
    base_url="<http://localhost:11434>",
    ollama_additional_kwargs={"mirostat": 0},
)
```

The resulting embeddings were saved to data/train_embeddings.npy.

### Note

In the future we will probably rent a server with high computing power to turn the rest of the comments into embeddings. It is also possible that a more accurate model such as Mistral will be used.

## Clustering Logic

For clustering, we implemented the k-means clustering algorithm from scratch. Initially, we used clustering_core/k-means-N_dim.cpp for embedding, but due to time constraints with larger datasets, we switched to using t-SNE for dimensionality reduction. The 2D k-means implementation can be found in clustering_core/k-means2D.cpp. The clustering results are saved in data/train_embeddings_clusters.csv, including cluster names and distances of each point from the cluster centroids.

## GUI

**This part of the project has not been implemented yet.** The choice of framework for building the GUI is pending. However, planned features include:

- Determining the most prevalent opinion over a specific time period.
- Creating an interactive 2D scatter plot using t-SNE.
- Assigning clusters to new comments.
- Displaying neighboring clusters for new comments.
- Naming clusters using the LLM model (e.g., Mistral).
- Providing information about each cluster, such as size and similarities.
- Displaying the top 10 comments for each cluster based on position and upvotes.
- Generating plots related to data and clusters, such as popular, unpopular, and controversial comments.

## Optimization Ideas

Handling 28 million comments on regular computers is challenging. To address this, we plan to use algorithms or Large Language Models to identify and present interesting comments from each cluster instead of visualizing all comments. Additionally, we aim to enable the transformation of new user comments into embeddings without running the LLM locally, facilitating the addition of new comments to the dataset.

# Usage

## To set python venv (for tourch, models, etc), run

```
python3 -m venv env
source env/bin/activate
```

to install all your dependencies within their own copy of the project:

```
pip install -r requirements.txt
```

## To run emmbading llm

download [ollama](https://ollama.com/download/mac), and follow the instructions
make sure that you have to initialize ollama before running the emmbedding algorithm

## to install g-tests

follow the [instructions](https://stackoverflow.com/questions/15852631/how-to-install-gtest-on-mac-os-x-with-homebrew). Proper, portable usage will be implemented later. (Like built-in CMake files.)