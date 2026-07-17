Project: Intermittent Data Collection from Low-Power LoRa Field Nodes

The examination of the idea of collecting data from LoRa Field Nodes and its construction of the firmware based on C.

The skeleton has 8 modules and their test files individually. We see PASS situtation in roughly all the tests;except the limitation examples. These modules are respectively;
1) Packet
2) Buffer
3) ScoringEngine
4) PullRequestHandler
5) NodeStateMachine
6) CollectorSimulator
7) MockHAL
8) Logger

Additionally, there is a test file that investigates the limitations of the modules' firmware construction. 
