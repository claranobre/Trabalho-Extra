#!/bin/bash
datainicial=`date +%s`

./client_socket0
./client_socket1
./client_socket2
./client_socket1
./client_socket3
./client_socket1
./client_socket4
./client_socket1
./client_socket5
./client_socket1
./client_socket6
./client_socket1
./client_socket7
./client_socket1
./client_socket8
./client_socket1
./client_socket9
./client_socket1
./client_socket0
./client_socket1
./client_socket2
./client_socket1
./client_socket3
./client_socket1
./client_socket4
./client_socket1
./client_socket5
./client_socket1
./client_socket6
./client_socket1
./client_socket7
./client_socket1
./client_socket8
./client_socket1
./client_socket9
./client_socket1
./client_socket0
./client_socket1
./client_socket2
./client_socket1
./client_socket3
./client_socket1
./client_socket4
./client_socket1
./client_socket5
./client_socket1
./client_socket6
./client_socket1
./client_socket7
./client_socket1
./client_socket8
./client_socket1
./client_socket9
./client_socket1
./client_socket0
./client_socket1
./client_socket2
./client_socket1
./client_socket3
./client_socket1
./client_socket4
./client_socket1
./client_socket5
./client_socket1
./client_socket6
./client_socket1
./client_socket7
./client_socket1
./client_socket8
./client_socket1
./client_socket9
./client_socket1

datafinal=`date +%s`
soma=`expr $datafinal - $datainicial`
resultado=`expr 10800 + $soma`
tempo=`date -d @$resultado +%H:%M:%S`
echo " Tempo gasto: $tempo "