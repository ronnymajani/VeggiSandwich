# VeggiSandwich
A Ceaser Cypher Encryptor/Decryptor CLI Tool

##Summary
This was a project that I did as extra credit for my finite mathematics class in my first undergraduate year of computer engineering.
It contains a few tools (sum which I admit are pointless) that can decypher or help analyze alphabetic text that has been ciphered using the classic vigenere and ceaser ciphers.

##Details and Features
- The entire program is written in pure C
- The program offers a few different tools that are called by the Ceaser Decipher tool but are made available if the user wishes to do any manual work
- The program has a history and save feature. Everytime you call the decipher tool, the result is appended to the end of the output file prefixed with a timestamp

##A Few Notes
- My code isn't that well documented (actually it isn't documented at all), as I was trying to finish the project on time, because I procrastinated doing it until I had a week left
- Some aspects of the code are reduntant and could have been implemented better.
- Despite my lack of documentation, I tried my best to comment as much as I could, but if there's any part that you're having difficulty understanding, feel free to message me and I'll be glad to help.
- At the time I wrote the code I wasn't that well informed about coding in compliance with the C Standard, I was only aware of whatever the compiler warned me about, so it is possible that some aspects of my code are non standard compliant.

##Building
I used *Code::Blocks* IDE for this project, but for the convenience of those whoe prefer getting their hands a little dirtier via **makefile**s and the terminal, I used *cbp2make* to generate **makefile**s out of the codeblocks project.
- To build the project using the makefiles just run the command `make -f makefile.*yourOS* [release] [debug]`
- available make files (yourOS types):
  - .unix
  - .mac
  - .windows
- *example:* `make -f makefile.unix release`
- if you don't specify the type of output you want (release and/or debug) the build will default to building for both (release AND debug)
- **Warning:** I was only able to test the .unix version makefile so unfortunatley I can't gurantee that the other two are functional.

