#!/usr/bin/env python3
# Jason Su @ 01/07/2023
from flask import Flask, request, render_template, jsonify
import time

app = Flask(__name__)
ind=0

@app.route("/", methods=['GET'])
def index():
    templateData = {
            'title' : 'LED Matrix',
        }
    return render_template('index.html',**templateData)

@app.route("/scripts/<script>", methods=['GET'])
def jscript(script):
    templateData = {
            'title' : 'LED Matrix',
        }
    file='scripts/'+ script
    return render_template(file,**templateData)

@app.route("/data", methods=['GET'])
def getData():
    templateData = {
            'title' : 'LED Matrix',
        }
    global ind
    f = open('../GPS_IMU_Fusion/accel.txt', 'r')
    f.seek(ind)
    line=f.readline()
    accel=line.split('\t')
    accelx=float(accel[0])
    print(accelx)
    data = {'accelx': accelx, 'ts': ind}
    ind=ind+len(line)
    return jsonify(data)

if __name__ == "__main__":
   app.run(host='172.19.98.231', port=8081)