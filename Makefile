build : compile
	./hash

compile : 
	gcc -o hash src/main.c src/hash_table.c 

valgrind : ./hash
	valgrind ./hash

add : ./.git
	git add .

commit : add 
	read -p -n 'Enter a meaningful comming message :\n + ' commit_message
	git  commit -m $commit_message 

push : commit 
	git push
