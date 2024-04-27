Basicaly it's a Project for Hiher school of Economics.
I do not choose embedding algorithms, and clastorisation algorithms, but it will include them. Also the GUI will be used.

## To set python venv (for tourch, models, etc), run:
```
python3 -m venv env
source env/bin/activate
```

to install all your dependencies within their own copy of the project:
``` 
pip install -r requirements.txt
```
## To run emmbading llm:
download [ollama](https://ollama.com/download/mac), and follow the instructions

## ideas:
    1. determine topmost opinion through timeperiod
    2. build the map, 2d representation, by t-SNE
    3. determine cluster for new comment (with deistances)
    4. reveal the cluster's neighbors for new comments
    5. show, determined by llm model, cluster's names
    6. sizes of clusters
    7. reveal top 10 comments of each cluster by cluster position
    8. reveal top 10 comments of each cluster by upvotes