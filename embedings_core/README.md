## To set python venv (mainly for tourch, pandas, and models), run:
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
