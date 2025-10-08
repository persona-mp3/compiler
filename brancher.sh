#/bin/bash


# target_branch=git branch -a | fzf
target=$(git branch  |  sed 's/* //' |fzf --height=40%  --margin=20% --tmux 30% --border)
if [  $? -ne 0  ]; then
	echo "fzf got cancelled"
	exit
fi

if [[ -z $target ]]; then
	echo "no branch selected"
	exit
fi

operation=$(git switch $target)
