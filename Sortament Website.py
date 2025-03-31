from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/instructions')
def instructions():
    return render_template('instructions.html')

@app.route('/begin')
def begin_process():
    return render_template('begin_process.html')

@app.route('/output', methods=['POST'])
def output():
    # Simulated example values
    data = {
        'weight': '342g',
        'type': 'PLA',
        'print_time': '4h 15m',
        'diameter': '1.75mm',
        'length': '112m',
        'cost_saved': '$7.90'
    }
    return render_template('output.html', **data)

if __name__ == '__main__':
    app.run(debug=True)
