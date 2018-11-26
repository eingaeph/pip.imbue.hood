extra() { echo $3; echo; cat -n $3 | sed -n "$1,+$2p" -; }

