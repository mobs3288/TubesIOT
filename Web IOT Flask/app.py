from flask import Flask, render_template, jsonify, request
from tensorflow.keras.models import load_model
import numpy as np
import random

# Route for home page
app = Flask(__name__)

# Load the pre-trained model
model = load_model('modelPredictTemp.h5', compile=False)
model.compile(optimizer='adam', loss='mean_squared_error')

weather_model = load_model('weather_prediction_model.h5', compile=False)
weather_model.compile(optimizer='adam', loss='mean_squared_error')

# Initialize sensor variables
sensor_data = {
    'temperature': None,
    'humidity': None,
    'light_hour': None,
    'raindrop': None
}

@app.route('/update_sensor_data', methods=['POST'])
def update_sensor_data():
    global sensor_data  # Use the global variable

    data = request.get_json()
    sensor_data['temperature'] = data.get('temperature')
    sensor_data['humidity'] = data.get('humidity')
    sensor_data['light_hour'] = data.get('sunshine_time')
    sensor_data['raindrop'] = data.get('rain_value')

    if (sensor_data['raindrop'] == 0):
        sensor_data['raindrop'] = 1
    else:
        sensor_data['raindrop'] = 0

    # Do something with the sensor data
    print("Received sensor data:")
    for key, value in sensor_data.items():
        print(f"{key}: {value}")

    return jsonify(sensor_data)  # Return the sensor data as JSON

def get_prediction(temperature):
    input_data = np.array([[temperature, 0]])
    return model.predict(input_data).tolist()

def get_weather_prediction():
    global sensor_data, scaler, label_encoder  # Use the global variables

    # Example input data from DHT11 and light sensor
    temperature = sensor_data['temperature']
    humidity = sensor_data['humidity']
    light_intensity = sensor_data['light_hour']
    raindrop = sensor_data['raindrop']

    # Create input data array
    input_data = np.array([[temperature, humidity, raindrop, light_intensity]])

    # Make predictions
    predictions = weather_model.predict(input_data)

    # Round the predicted values to the nearest integer
    rounded_predictions = np.round(predictions).astype(int)

    return rounded_predictions.tolist()

@app.route('/')
def home():
    return render_template('predict_temperature.html')

@app.route('/get_prediction', methods=['GET'])
def get_prediction_route():
    global sensor_data  # Use the global variable

    prediction = get_prediction(sensor_data['temperature'])
    weather_prediction = get_weather_prediction()

    # Now, 'rounded_prediction_int' contains the list of rounded and integer values

    return jsonify({'temperature_prediction': prediction, 'weather_prediction': weather_prediction[0], 'sensor_data': sensor_data})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
