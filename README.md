# IoT Weather Prediction System

## Introduction

### Background

In the rapidly evolving digital era, Internet of Things (IoT) technology plays a crucial role in transforming various aspects of human life. This project focuses on predicting temperature and weather conditions using IoT technology.

### Problem Statement

Accurate weather predictions are essential in various fields such as agriculture, transportation, energy, and health. Traditional weather stations are limited in their coverage, prompting the need for a more sophisticated and integrated solution for monitoring and predicting temperature and weather conditions.

### Objectives

1. Improve user experience in obtaining accurate weather information.
2. Implement a real-time data acquisition system.
3. Develop a data processing pipeline for weather prediction.

## Theoretical Foundation

### Related Work

Several studies have addressed the prediction of temperature and weather conditions using IoT and machine learning technologies. Notable works include Mishra et al.'s precision agriculture in smart cities [1] and Singh et al.'s IoT live weather monitoring system using NodeMCU ESP8266 [2].

### IoT (Internet of Things)

The concept of IoT involves embedding physical objects or devices with technologies like sensors and software to enable communication, control, and data exchange over the internet.

### Direct HTTP

Direct HTTP refers to the direct communication between a client and a server using Hypertext Transfer Protocol (HTTP) without additional protocol layers, enabling immediate data exchange.

### MLP (Multi-Layer Perceptron)

MLP is a type of neural network consisting of an input layer, one or more hidden layers, and an output layer. It is widely used in machine learning for various tasks.

## Methodology

### MLP Implementation

We implemented a Multi-Layer Perceptron (MLP) model for weather prediction. The model consists of an input layer with 64 neurons, a hidden layer with 32 neurons, and an output layer activated by softmax. The model achieved high accuracy on both training and validation sets, demonstrating its ability to generalize well.

### Results

The final evaluation on the test set showed an accuracy of 94.54%. The model performed well, indicating its effectiveness in predicting weather conditions based on provided features.

## Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/iot-weather-prediction.git

2. Install dependencies:

   ```bash
   pip install -r requirements.txt

3. Run the application:

   ```bash
   python app.py

## Contributors

- **Ryan Oktaviandi Susilo Wibowo** (1301204289)
- **M. Sulthon Sayid Abdurrohman** (1301204089)
- **Novaldi Ramadhan Waluyo** (1301204423)

## References

1. Mishra et al., "IoT and machine learning for precision agriculture in smart cities"
2. Singh et al., "IOT LIVE WEATHER MONITORING SYSTEM USING NODEMCU ESP8266"
3. Araujo and Andrade, "Post-Processing Air Temperature Weather Forecast Using Artificial Neural Networks"
4. Bayı lmıs ̧ et al., "A survey on communication protocols and performance evaluations for Internet of Things"
