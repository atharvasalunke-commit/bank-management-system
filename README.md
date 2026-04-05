# bank-management-system

\# Bank Management System



A terminal-based banking system built in C++ with MySQL database integration.



\## Features

\- User registration and login with bcrypt password hashing

\- transactions like deposit, withdraw and check balance.

\- Transfer between accounts

\- Transaction history of account

\- Account verification via account ID and PIN



\## Tech Stack

\- C++ VISUAL STUDIO

\- MySQL WORKBENCH

\- MySQL Connector C++ 9.6

\- bcrypt for password hashing





\## Build Setup

1\. Install Visual Studio with Desktop C++ workload

2\. Install MySQL Connector C++ 9.6

3\. Configure include and lib paths in project properties (Release x64)

4\. Copy DLLs from Connector lib64 folder to output directory



\## Project Structure

\- main.cpp — entry point

\- customer.cpp/h — banking operations

\- Database.cpp/h — MySQL operations

\- base\_of\_details.cpp/h — user credentials

\- DATABASE.sql — database schema

