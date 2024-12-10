//Overview
AdvisorBot is a command-line program that helps users make investment decisions 
based on a set of pre-defined commands. It provides feedback, guides users through valid input, 
and processes various commands to retrieve investment data. 
The bot is built with Object-Oriented Programming (OOP) principles, 
leveraging code from a previous project (Merkelrex) to handle data and input parsing.


//Features

Command-Line Interface (CLI): AdvisorBot allows users to interact with the program using text-based commands.

Input Validation: Checks for invalid, empty, or incorrect commands and provides helpful error messages.

Data Retrieval: Interacts with a dataset of products to perform operations 
such as finding minimum/maximum values, calculating averages, and making predictions.

Help Command: The help command provides assistance with valid inputs, 
and help<cmd> provides examples for specific commands.


//Technologies Used

C++
Object-Oriented Programming


//Key Functions

Tokeniser: Parses commands into tokens using separators such as spaces or commas. It stores these tokens in a vector for processing.

Input Checker: Validates user input to ensure commands are not empty or invalid.

getData: Retrieves relevant product data based on the user's commands and performs necessary calculations like max, min, and avg.

cmdReader: Reads and processes the commands entered by the user, calling appropriate functions based on the command.
