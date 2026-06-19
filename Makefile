build : compile
	./hash

compile : 
	gcc -o hash  src/main.c src/hash_table.c src/prime.c  -lm 

valgrind : 
	valgrind --leak-check=full ./hash

add : ./.git
	git add .

commit : add 
	echo -n "Add a meaningful commint message :\n + "
	read commit_message
	git  commit -m $commit_message 

push : commit
		git push
