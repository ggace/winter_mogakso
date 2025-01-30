from flask import Flask, render_template, make_response
import config
import json

app = Flask(__name__, static_folder="static")
app.config['JSON_AS_ASCII'] = False
 
API_KEY = config.API_KEY
with open("data/university.json", 'r', encoding='UTF-8') as f:
    result = json.load(f)

    res = json.dumps(result, ensure_ascii=False, indent=4)
    
    

@app.route('/')
def index():
  UNIVERSITY_LIST = make_response(res)
  return render_template('index.html', API_KEY=API_KEY)
 
@app.route('/search')
def about():
    return render_template('search.html')

@app.route("/university.json")
def university_json():
    UNIVERSITY_LIST = make_response(res)
    return UNIVERSITY_LIST



if __name__ == "__main__":
   app.run(debug=True, port=5500)