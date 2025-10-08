#/bin/bash


# target_branch=git branch -a | fzf
curr_branches=$(git branch)
target=$(git branch  | fzf --height=40%  --margin=20% --tmux 30% --border)
if [  $? -ne 0  ]; then
	echo "fzf got cancelled"
	exit
fi

if [[ -z $target ]]; then
	echo "no branch selected"
	exit
fi

echo "$target"
operation=$(git checkout $target)
# echo "$operation"
