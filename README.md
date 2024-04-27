Basicaly it's a Project for Hiher school of Economics.
I do not choose embedding algorithms, and clastorisation algorithms, but it will include them. Also the GUI will be used.

## To set python venv (for tourch, models, etc), run:
```
python3 -m venv emb_venv
source env/bin/activate
```

to install all your dependencies within their own copy of the project:
``` 
pip install -r requirements.txt
```
## To run emmbading llm:
download [ollama](https://ollama.com/download/mac), and follow the instructions
then run the following code to install and run llm model:
```
ollama run all-minilm
```