export PATH=/applications
export TERM=vt100
export RUBYLIB=/libraries/ruby

if [ "$TERM" != "dumb" ]; then
    eval "`dircolors -b`"
    alias ls='ls --color=auto'
fi

export PS1="\[\e[34;1m\][\t]\[\e[0m\] \w \[\e[34;1m\]$\[\e[0m\] "

echo "Welcome to the Pedigree operating system.

Please don't feed the code monkeys - they bite."
