# Cryptocurrency Address Swap Detection
Alerts the user when the clipboard changes from one cryptocurrency address to another in a short period of time.

# Usage
By default, a warning will be instantiated if the clipboard changes from one cryptocurrency address to another in <1 second.
<br>
To alter the sensitivity, provide a float as the first argument which is the multiplier for 1 second.
<br>
E.g. 0.5 = 1/2 second sensitivity.
