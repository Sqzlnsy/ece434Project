#!/usr/bin/env python3
# Jason Su @ 01/07/2023
from flask import Flask, request, render_template, jsonify
import time
import math
ACCEL_X = 1
ACCEL_Y = 2
ACCEL_Z = 3
ACCEL_VELX = 4
ACCEL_VELY = 5
ACCEL_VELZ = 6


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
k = 10

@app.route("/time", methods=['GET'])
def getTime():
    data = {'time': 1676076002}
    #data = {'time': int(time.time())}
    return jsonify(data)

@app.route("/data/<type>=<num>", methods=['GET'])
def getData(type, num):
    templateData = {
            'title' : 'LED Matrix',
        }
    num = int(num)
    k = type.split('-')
    
    file_name = k[0]+".log"
    col = int(k[1])
    print ("filename = "+ file_name + "  col = ",col)
    f = open("data/"+file_name,'r')

    #f = open('../GPS_IMU_Fusion/accel.txt', 'r')
    time_Stamp = []
    data = []
    #lines = f.readlines()[-int(k):-int(k-num)]
    lines = f.readlines()[-int(num):]
    f.close()
    for line in lines:
        temp = line.split(' ')
        time_Stamp.append(temp[0])
        if (file_name != "vel.log"):
            data.append(temp[col])
        else:
            data.append(math.sqrt(temp[0]**2+temp[1]**2+temp[2]**2))
    #print(data)
    d = {'param': data, 'ts': time_Stamp}
    return jsonify(d)

if __name__ == "__main__":
   app.run(host='0.0.0.0', port=8082)