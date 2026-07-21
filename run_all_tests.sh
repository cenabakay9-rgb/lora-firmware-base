#!/bin/bash

echo "================================"
echo "Modul1:Packet"
echo "================================"
gcc test_packet.c -o test_packet
./test_packet
echo ""

echo "================================"
echo "Modul2:Buffer"
echo "================================"
gcc scoring.c buffer.c test_buffer.c -o test_buffer
./test_buffer
echo ""

echo "================================"
echo "Modul3:ScoringEngine"
echo "================================"
gcc scoring.c test_scoring.c -o test_scoring
./test_scoring
echo ""

echo "================================"
echo "Modul4:PullRequestHandler"
echo "================================"
gcc scoring.c buffer.c pull.c test_pull.c -o test_pull
./test_pull
echo ""

echo "================================"
echo "Modul5:NodeStateMachine"
echo "================================"
gcc scoring.c buffer.c pull.c node_fsm.c test_node_fsm.c -o test_node_fsm
./test_node_fsm
echo ""

echo "================================"
echo "Modul6:CollectorSimulator"
echo "================================"
gcc scoring.c buffer.c pull.c node_fsm.c collector.c test_collector.c -o test_collector
./test_collector
echo ""

echo "================================"
echo "Modul7:MockHAL"
echo "================================"
gcc hal.c test_hal.c -o test_hal
./test_hal
echo ""

echo "================================"
echo "Modul8:Logger"
echo "================================"
gcc scoring.c buffer.c pull.c logger.c test_logger.c -o test_logger
./test_logger
echo ""

echo "================================"
echo "LimitationCasesTests"
echo "================================"
gcc scoring.c buffer.c pull.c node_fsm.c collector.c test_limitation_cases.c -o test_limitation_cases
./test_limitation_cases
echo ""

echo "================================"
echo "TUM TESTLER TAMAMLANDI!"
echo "================================"