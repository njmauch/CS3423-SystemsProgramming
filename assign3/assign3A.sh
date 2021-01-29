awk -F: '{split($5,s, " "); print s[2]}' $1 | sort | while read index; do awk -v var=$index -F: '$5~var{print $0}' $1; done
