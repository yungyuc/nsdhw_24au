PoissonNet
****************************

This project aims to simulate 
network packet arrivals using Poisson processes 
with priority-based queueing, 
providing a C++ engine and 
a Python API for efficient network traffic analysis.

****************************
Basic Information
****************************

**Project**: PoissonNet

**GitHub**: https://github.com/chris901003/PoissonNet

****************************
Problem to Solve
****************************
In modern network systems, understanding and simulating the 
behavior of packet arrivals is crucial for optimizing performance, 
managing traffic, and ensuring system reliability. 
One of the common models for simulating random events over time is 
the Poisson process, which is widely used to represent 
the arrival of packets in a network.

However, network environments are often more complex, 
involving multiple streams of data packets with 
varying priority levels and dynamic arrival rates. 
The challenge is to simulate not only the random arrival of packets 
using Poisson processes but also to model the 
priority-based processing of these packets at a service station, 
where higher priority packets are served first. Additionally, 
the system must account for fluctuating packet arrival rates 
during peak and off-peak periods.

By addressing this problem, 
we can create a simulation library that helps network engineers 
and researchers better understand packet flow dynamics, 
optimize service performance, and improve overall network efficiency.

****************************
Prospective Users
****************************

1. Network Engineers: Professionals responsible for designing 
and maintaining network infrastructures can use this library to 
simulate packet flows, analyze traffic patterns, 
and optimize network performance under various conditions.

2. Developers of Network Simulators: 
Developers creating larger-scale network simulation platforms 
can integrate this library into their tools to 
add advanced packet arrival and queueing models 
based on Poisson processes.

****************************
System Architecture
****************************

**Core Components**:

1. Implements the Poisson process to simulate random packet arrivals.
  - We will use exponential distribution random variables to model the inter-arrival times of packets.
  - In test I will ensure that the randomly generated numbers are fixed by using a fixed seed.
2. Supports multiple streams of data packets with varying arrival rates.
3. Handles priority-based packet processing with a queue system.
4. Provides high-performance computation through optimized algorithms.

**API Components**:

1. Provides a simple, user-friendly Python interface 
for users to interact with the C++ simulation engine.
2. Allows users to configure simulation parameters 
(arrival rates, priority levels, service rates) 
and retrieve simulation results.

****************************
API Description
****************************

.. code:: python

    import poisson_simulator
    import matplotlib.pyplot as plt

    # 設定模擬參數
    lambda_high = 5.0  # 高優先級流的到達率
    lambda_medium = 3.0  # 中優先級流的到達率
    lambda_low = 1.0  # 低優先級流的到達率
    duration = 10.0  # 模擬持續時間為 10 秒

    packets = poisson_simulator.simulate_multi_priority_packets(lambda_high, lambda_medium, lambda_low, duration)

    print("Packet Arrival Times and Priorities:")
    for packet in packets:
        print(f"Arrival Time: {packet['arrival_time']} seconds, Priority: {packet['priority']}")

    poisson_simulator.process_packets(packets)

    arrival_times = [packet['arrival_time'] for packet in packets]
    priorities = [packet['priority'] for packet in packets]

    plt.figure(figsize=(10, 5))
    plt.scatter(arrival_times, priorities, c=priorities, cmap='coolwarm', s=100, alpha=0.7)
    plt.title('Packet Arrivals with Different Priorities')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Priority Level')
    plt.colorbar(label='Priority')
    plt.grid(True)
    plt.show()


****************************
Engineering Infrastructure
****************************

Use Makefile and Shell scripts to buid the project.
Use GitHub Actions to verify that the build works correctly.

Schedule
========

* Week 3 (09/16): Proposal Submission
* Week 4 (09/23): Setup Development Environment and CI/CD Pipeline
* Week 5 (09/30): Implement Poisson processes
* Week 6 (10/07): Implement Priorities system
* Week 7 (10/14): Integration and Testing
* Week 8 (10/21): Develop API Components
* Week 9 (10/28): Develop API Components
* Week 10 (11/04): Build Pytyon Library
* Week 11 (11/11): Create build scripts and CI/CD pipeline
* Week 12 (11/18): Advanced Features and Dynamic Testing
* Week 13 (11/25): Improve Analysis Performance
* Week 14 (12/02): Prepare Final Report
