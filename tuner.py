# -*- coding: utf-8 -*-
import numpy as np
import serial

# Nazwiazanie polaczenia z Arduino poprzez port szeregowy
port = "COM8"
sio = serial.Serial(port, 115200)
sio.close()
sio.open()
sio.readline()
# Wyslanie sygnalu rozpoczecia transmisji danych 
sio.write("Tak!".encode('ascii'))

# Deklaracja zmiennych
N = 0
n = np.arange(N)
freq = None
t = 0

    
# Petla interpretacji danych
while True:
    dane = []
    t = 0
    N = 0
    
    while not t:
        line = sio.readline()
        try:
            # Odczyt wysylanych przez mikrokontroler
            # danych z mikrofonu
            temp = float(line)
            dane.append(temp)
            N = N + 1
        except ValueError:
            # Odczyt czasu trwania pomiarow
            if 'Czas' in str(line[:4]):
                t = sio.readline()
                t = int(t[:3])
     
    dane = np.array(dane)
    n = np.arange(N)

    F = (n/(t*0.001))   # Przedzial czestotliwosci
    fft = np.fft.fft(dane)   # Szybka transformata F. danych
    mod = np.abs(fft)
    
    l = np.argmax(mod[1:(N+1)/2])   # Pobranie indeksu maksymalnego argumentu
    freq = F[l]   # Odczyt wartości na maksymalnego argumentu
    
    print(freq, 'Hz')
    # Blok kontrolujacy zapalanie diod
    if 325.0 < freq < 327.0:
        sio.write("3".encode('ascii'))
    elif 244.0 < freq < 246.0:
        sio.write("5".encode('ascii'))
    elif 384.5 < freq < 386.5:
        sio.write("6".encode('ascii'))
    elif 286.0 < freq < 288.0:
        sio.write("9".encode('ascii'))
    elif 107.0 < freq < 109.0:
        sio.write("0".encode('ascii'))
    elif 160.0 < freq < 162.0:
        sio.write("1".encode('ascii'))
