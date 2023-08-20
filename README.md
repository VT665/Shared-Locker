# Shared-Locker
This program contains of 2 modules, namely use module and configure module.

The program implements user interface through a menu system.
Users are prompted to input their choice by selecting a number corresponding to Use, Configure and Exit options.
The program validates the user input, and calls the corresponding function.

The "Use" module allows users to access shared lockers by providing their locker ID and all the user keys.
It prompts the users to enter the locker ID they want to access.
It searches for the locker ID in the "config.txt" file to determine if the locker exists.
If the locker is found, it prompts the users to enter their user keys.
It calculates the locker access key by finding a number that meets specific criteria involving user keys and prime numbers.
Finally, it displays the locker access key to the user, allowing them to open the locker.

The "Config" module is responsible for configuring (adding or deleting) lockers.
It presents a menu to the user with options to add a new locker, delete an existing locker, or return to the main menu.
When selecting "Add new locker," it takes input for locker ID, locker key, and the number of users for the new locker and checks for duplicates in the "config.txt" file.
It generates primes and user keys for each user, shares the keys with the user and stores the primes along with locker id in the "config.txt" file.
If the user chooses "Delete locker," they input the locker ID to be deleted. The module then removes the corresponding entry from "config.txt".
