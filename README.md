# Cryptocurrency Address Swap Detection
Alerts the user when the clipboard changes from one cryptocurrency address to another in a short period of time.

See an example of it being used [here](https://www.youtube.com/watch?v=mwYYFLqA4KU).

# Description
Some malware will detect a cryptocurrency address in the victims' clipboard and exchange it with a different one, in hopes that the user will deposit cryptocurrency to the exchanged address. A demonstration of such malware can be found in [another of my repositories](https://github.com/Charlie-Gallie/Bitcoin-Address-Swapper).
<br>
This program alerts the user when the clipboard changes from one cryptocurrency address to another in a short period of time.
<br>
This currently only works with most Bitcoin address formats - No other cryptocurrencies.

# Usage
By default, a warning will be instantiated if the clipboard changes from one cryptocurrency address to another in <1 second.
<br>
To alter the sensitivity, provide a float as the first argument which is the multiplier for 1 second.
<br>
E.g. 0.5 = 1/2 second sensitivity.
