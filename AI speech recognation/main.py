import serial
import speech_recognition as sr
import time

# Initialize serial communication with Arduino
try:
    arduino = serial.Serial('COM7', 9600, timeout=1)
    time.sleep(2)  # Allow time for the connection to establish
    print("Connected to Arduino on COM7")
except serial.SerialException as e:
    print(f"Error connecting to Arduino: {e}")
    exit()

# Initialize the recognizer
recognizer = sr.Recognizer()

# Function to send command to Arduino
def send_command(command):
    try:
        if arduino.is_open:
            arduino.write((command + '\n').encode())
            print(f"Sent to Arduino: {command}")
        else:
            print("Arduino connection is closed.")
    except Exception as e:
        print(f"Error sending command: {e}")

# Function to listen for a command
def listen_for_command():
    with sr.Microphone() as source:
        print("Listening for command...")
        try:
            # Adjust ambient noise and listen for audio
            recognizer.adjust_for_ambient_noise(source, duration=1)
            audio = recognizer.listen(source, timeout=5)

            # Recognize the speech using Google Speech Recognition
            command = recognizer.recognize_google(audio).lower()
            print(f"Command recognized: {command}")
            return command

        except sr.UnknownValueError:
            print("Sorry, I could not understand the audio.")
        except sr.RequestError as e:
            print(f"Speech recognition service error: {e}")
        except sr.WaitTimeoutError:
            print("Listening timed out while waiting for input.")

    return None

# Main loop to continuously listen for commands
def main():
    print("Starting command listener. Say 'exit' to quit.")
    while True:
        command = listen_for_command()
        if command:
            if command in ["exit", "quit"]:
                print("Exiting program.")
                break

            send_command(command)

    # Close the serial connection when done
    if arduino.is_open:
        arduino.close()
        print("Arduino connection closed.")

if __name__ == "__main__":
    main()






