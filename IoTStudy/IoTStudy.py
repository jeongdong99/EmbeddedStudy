import drivers

from datetime import datetime

from time import sleep

import time

import board

import adafruit_dht

from picamera import PiCamera

from urllib.request import urlopen
from bs4 import BeautifulSoup

import RPi.GPIO as GPIO

dhtDevice = adafruit_dht.DHT11(board.D18)

camera = PiCamera()

display = drivers.Lcd()

pir = 14

GPIO.setup(pir, GPIO.IN)

print("Sensor initializing...")

time.sleep(2)

ledpin = 12  # PWM pin connected to LED

ledpin2 = 19

GPIO.setwarnings(False)  # disable warnings

GPIO.setmode(GPIO.BCM)  # set pin numbering system

GPIO.setup(ledpin, GPIO.OUT)

GPIO.setup(ledpin2, GPIO.OUT)

pi_pwm = GPIO.PWM(ledpin, 1000)

pi_pwm2 = GPIO.PWM(ledpin2, 1000)

pi_pwm.start(0)  # start PWM of required Duty Cycle

pi_pwm2.start(0)

url = "https://weather.com/weather/today/l/2745ada22b66132f6704578280408ddd4f7748093426584663aefe0bdc4491c6"

html = urlopen(url).read()

soup = BeautifulSoup(html, 'html.parser')

dhtDevice = adafruit_dht.DHT11(board.D18)

now = datetime.now()

str(now)

strNow = now.strftime('%Y-%m-%d %H:%M')

display = drivers.Lcd()

while True:
    try:
        temperature_c = dhtDevice.temperature

        humidity = dhtDevice.humidity

        tem_str = str(temperature_c)

        hum_str = str(humidity)

        discomfortIndex = (1.8 * temperature_c) - (0.55 * (1 - humidity / 100) * (1.8 * temperature_c - 26)) + 32

        if discomfortIndex > 75:

            pi_pwm2.ChangeDutyCycle(0)

            for duty in range(0, 101, 1):
                pi_pwm.ChangeDutyCycle(duty)

                pi_pwm2.ChangeDutyCycle(0)

                sleep(0.01)

            sleep(0.5)

        if discomfortIndex <= 75:

            pi_pwm.ChangeDutyCycle(0)

            for duty in range(0, 101, 1):
                pi_pwm2.ChangeDutyCycle(duty)

                sleep(0.01)

            sleep(0.5)

        weather = soup.find(class_='CurrentConditions--phraseValue--2Z18W')

        display.lcd_display_string(strNow, 1)  # Write line of text to first line of display

        display.lcd_display_string("Temp:" + tem_str + "C " + "Hum:" + hum_str + "%", 2)

        sleep(2)

        display.lcd_display_string("weather : " + weather.text + " ", 2)

        sleep(2)

        display.lcd_clear()

        sleep(0.5)

        print("Writing to LCD Display")

        if GPIO.input(pir) == True:

            print("Motion Detected!")

            basename = "sjd"

            suffix = datetime.now().strftime("%Y%m%d_%H%M%S") + '.h264'

            filename = "_".join([basename, suffix])

            camera.resolution = (640, 480)

            camera.start_preview()

            sleep(3)

            camera.start_recording('/home/pi/Python/' + filename)

            camera.wait_recording(10)

            camera.stop_recording()

            i = 0

            while i < 3:
                display.lcd_display_string('Motion Detected!', 1)

                pi_pwm.ChangeDutyCycle(100)

                pi_pwm2.ChangeDutyCycle(100)

                sleep(1)

                display.lcd_clear()

                pi_pwm.ChangeDutyCycle(0)

                pi_pwm2.ChangeDutyCycle(0)

                sleep(1)

                i += 1

            # camera.start_preview()

            # camera.capture("sjd.jpg")

            # camera.stop_preview()

    except RuntimeError as error:

        print(error.args[0])

        continue

    except Exception as error:

        dhtDevice.exit()

        raise error

        time.sleep(2.0)


    except KeyboardInterrupt:

        # If there is a KeyboardInterrupt (ctrl+c), exit the program and cleanup

        print("Cleaning up!")

        display.lcd_clear()

