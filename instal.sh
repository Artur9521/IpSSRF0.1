#!/bin/bash
g++ -c main.cpp
g++ main.o -o program
touch run
echo "#!/bin/bash" > run
echo "SCRTORUN=\"./program\"">> run
echo "gnome-terminal -- bash -c \"\$SCRTORUN; exec bash\"" >> run
chmod ugo+x run
rm instal.sh
